#include "nn.h"

void fc(int m, int n, const float *x, const float *A, const float *b, float *y) {
  int i,j,k;
  k = 0;
  for(i=0; i<m; i++) {
    float z = 0;
    for(j=0; j<n; j++) {
      z += *(A+j+k) * *(x+j);
    }
    *(y+i) = z + *(b+i);
    k += n;
  }
} //y=10 式(1) ,この時の入力x(=784)はfc_inに記憶

void relu(int m, const float *x, float *y) {
  //入力 10→n 前回の出力y(=10)→x, y=出力
  int i;
  for(i=0; i<m; i++) {
    if (*(x+i)>0) {
      *(y+i) = *(x+i);
    } else if(*(x+i)<=0) {
      *(y+i) = 0;
    }
  }
} // → 式(2) → 出力y(=10),この時の入力x(前回の出力=10)は記憶

void softmax(int m, const float *x, float *y) {
  //入力 10→n 前回の出力y(=10)→x, y=出力
  int i,z=0;
  float max = *x;
  for (i=1; i<m; i++) {
    if (max <= *(x+i)) {
      max = *(x+i);
    }
  }
  for(i=0; i<m; i++) {
    z += exp(*(x+i)+max);
  }
  for(i=0; i<m; i++) {
    *(y+i) = (exp(*(x+i)+max)) / z;
  }
} // → 式(2) → 出力y(=10),ここまでが３層

// inference3(A, b, test_x + j*width*height, y2)
int inference3(const float *A, const float *b, const float *x,float *y) {
  fc(10, 784, x, A, b, y);
  relu(10, y, y);
  softmax(10, y, y);
  float max = *y;
  int i,num = 0;
  for (i=1; i<10; i++) {
    if (max < *(y+i)) {
        num = i;
    }
  }
  return num;
}

void memory(int n, float * x, float * o) {
  int i;
  for(i=0;i<n;i++) {
    o[i] = x[i];
  }
}

void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dA, float *db) {
  int i;
  float *FC_in1 = malloc(sizeof(float)*784);
  float *FC_in2 = malloc(sizeof(float)*50);
  float *FC_in3 = malloc(sizeof(float)*100);
  float *ReLU_in1 = malloc(sizeof(float)*50);
  float *ReLU_in2 = malloc(sizeof(float)*100);
  memory(784,x,FC_in1) //FC1への入力を記憶
  fc(50, 784, x, A, b, y); //FC1層
  memory(50,y,ReLU_in1) //ReLU1層の入力を記憶
  relu(50, y, y); //ReLU1層
  memory(50,y,FC_in2) //FC2への入力を記憶
  fc(100, 50, y, A, b, y); //FC2層
  memory(100,y,ReLU_in2) //ReLU2層の入力を記憶
  relu(100, y, y); //ReLU2層
  memory(100,y,FC_in3); //FC3層の入力を記憶
  fc(10, 100, y, A, b, y); //FC3層
  softmax(10, y, y); //Softmax層
  // int ans = inference3(y);
  // loss(y, t);
  softmaxwithloss_bwd(10, y, t, y);
  // //勾配ベクトル 今 y には dx が入っている
  // print(1, 10, relu_in);
  relu_bwd(10, relu_in, y, y);
  // // //(10, 入力(db), 現在のdx, 出力(dx)の箱)
  fc_bwd(10, 784, fc_in, y, A, dA, db, fc_in);
  // この時点で yにはdx
  // (10, 784, x, dx, A, b, 出力(dx)の箱)

}

void print(int m, int n, const float *y) {
  int i,j,k;
  k = 0;
  for(i=0; i<m; i++) {
    for(j=0; j<n; j++) {
      printf("%.4f ", *(y+j+k));
    }
    printf("\n");
    k += n;
  }
}

int main() {
  float * train_x = NULL;
  unsigned char * train_y = NULL;
  int train_count = -1;

  float * test_x = NULL;
  unsigned char * test_y = NULL;
  int test_count = -1;

  int width = -1;
  int height = -1;

  load_mnist(&train_x, &train_y, &train_count,
             &test_x, &test_y, &test_count,
             &width, &height);

  float *y = malloc(sizeof(float)*10); //train_xの出力
  float *y2 = malloc(sizeof(float)*10); //train_xの出力
  float *A = malloc(sizeof(float)*784*10); //paramater A
  float *b = malloc(sizeof(float)*10); //paramater b
  float *dA = malloc(sizeof(float)*784*10); //勾配ベクトルdA
  float *db = malloc(sizeof(float)*10); //勾配ベクトルdb
  float *dAs = malloc(sizeof(float)*784*10); //ΣdA
  float *dbs = malloc(sizeof(float)*10); //Σdb
  // int *index = malloc(sizeof(int)*60000); //train_count

  rand_init(784*10, A); //Aを-1~1に初期化
  rand_init(10, b); //bを-1~1に初期化
  int i,j,k;
  for(i=0;i<10;i++) { // (5)エポック回数(10回)繰り返す
    for(j=0;j<60000;j++) { //(5-a)
      index[j] = j;
    } //初期化
    shuffle(60000, index);
    // print(1,10,b);
    for(j=0;j<600;j++) { //(5-b) 学習回数(600)回繰り返す
      init(784*10, 0, dAs); //dAsを0で初期化 (5-b-i)
      init(10, 0, dbs); //dbsを0で初期化 (5-b-i)
      for (k=0;k<100;k++) { //(5-b-ⅰ,ⅱ) n回のdA,dbの平均
        init(784*10, 0, dA); //dbsを0で初期化 (5-b-i)
        init(10, 0, db);
        backward6(A, b, train_x + 784*index[k], train_y[index[k]], y, dA, db);
        check(10,db);
        check(10*784,dA);
        add(10*784,1,dA,dAs);
        add(10,1,db,dbs);
      }
      scale(10*784, 0.01, dAs); //平均勾配を得る(5-b-ⅳ)
      scale(10, 0.01, dbs);
      // print(1,10,dbs);
      add(10*784,-0.01,dAs,A);
      add(10,-0.01,dbs,b);
    }
    // print(1,10,b);

    // print(1,10,b);
    int sum = 0;
    for(j=0; j<test_count; j++) { //(C)
      if(inference3(A, b, test_x + j*width*height, y2) == test_y[j]) {
        sum++;
      }
    }

    // print(1,10,b);
    printf("%f%%\n", sum * 100.0 / test_count);
    float z=0;
    for(j=0; j<test_count; j++) {
      output(A, b, test_x + j*width*height, y2);
      // printf("%f \n", y[train_y[1]]);
      // printf("%d \n", train_y[1]);
      z += loss(y2[train_y[j]], train_y[j]);
    }
    printf("%f\n", z/test_count);
  }
  return 0;
}
