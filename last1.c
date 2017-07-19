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
    } else if (*(x+i)<0) {
      *(y+i) = 0;
    }
  }
} // → 式(2) → 出力y(=10),この時の入力x(前回の出力=10)は記憶

void softmax(int n, const float *x, float *y) {
  int i;
  float z=0;
  float max = *x;
  for (i=1; i<n; i++) {
    if (max <= *(x+i)) {
      max = *(x+i);
    }
  }
  for(i=0; i<n; i++) {
    z += exp(*(x+i)-max);
  }
  for(i=0; i<n; i++) {
    *(y+i) = expf(*(x+i)-max) / z;
  }
}

int inference6(const float *A1, const float *b1,const float *A2, const float *b2, const float *A3, const float *b3, const float *x, float *y) {
  int i,num=0;
  float max = y[0];
  float *y1 = malloc(sizeof(float)*50);
  float *y2 = malloc(sizeof(float)*100);
  fc(50, 784, x, A1, b1, y1); //FC1層
  // memory(50,y,ReLU_in1); //ReLU1層の入力を記憶
  relu(50, y1, y1); //ReLU1層
  // memory(50,y,FC_in2); //FC2への入力を記憶
  fc(100, 50, y1, A2, b2, y2); //FC2層
  // memory(100,y,ReLU_in2); //ReLU2層の入力を記憶
  relu(100, y2, y2); //ReLU2層
  // memory(100,y,FC_in3); //FC3層の入力を記憶
  fc(10, 100, y2, A3, b3, y); //FC3層
  softmax(10, y, y); //Softmax層
  for (i=1; i<10; i++) {
    if (max < y[i]) {
        num = i;
        max = y[i];
    }
  }
  return num;
}

float cross_entropy_error(const float *y, int t) {
  return -1*1*log(*(y+t)+(1e-7));
}

// softmaxwithloss_bwd(10, y, t, y);
void softmaxwithloss_bwd(int m, const float *y, unsigned char t, float *dx) {
  int i;
  for(i=0;i<m;i++){
    if (i==t) {
      *(dx+i) = *(y+i) - 1;
    } else {
      *(dx+i) = *(y+i);
    }
  }
}
// // relu_bwd(10, relu_in, y, y);
void relu_bwd(int m, const float *x, const float *dy, float *dx) {
  int i;
  for(i=0;i<m;i++)
    if (*(x+i)>0) {
      *(dx+i) = *(dy+i);
    } else if (*(x+i)<=0) {
      *(dx+i) = 0;
    }
}

void fc_bwd(int m, int n, const float *x, const float *dy, const float *A, float *dA, float *db, float *dx) {

  int i,j;
  // dA = dy・x(T)
  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      *(dA+i*n+j) = *(dy+i) * *(x+j);
    }
  }
  // db = dy
  for (i=0;i<m;i++) {
    *(db+i) = *(dy+i);
  }

  // dx = A(T) × dy
  float AT[m][n];
  float BT[n][m];
  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      AT[i][j] = A[n*i+j];
    }
  } //一次元→二次元配列に変換
  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      // *(*(A+i)+j) = *(*(A+j)+i); //Aを転置
      BT[j][i] = AT[i][j];
    } //転置行列を作る
  }

  for (i=0;i<n;i++) {
    float z=0;
    for (j=0;j<m;j++) {
      z += BT[i][j] * dy[j];
    }
    *(dx+i) = z;
  } //前から10個ずつ取っていく
}

// void rand_init(int n, float * o) {
// // o[i] を [-1:1] の乱数で初期化
//   int i;
//   srand((unsigned) time(NULL));
//   for(i=0;i<n;i++){
//     float x;
//     x=(rand()%2000);
//     x=x/1000-1;
//     o[i]=x;
//   }
// }

void rand_init(int n, int m,float * o) {
// o[i] を [-1:1] の乱数で初期化
  int i;
  srand((unsigned)time(NULL)+m);
  for(i=0;i<n;i++){
    float x;
    x=(rand()%1000);
    x=x/1000;
    o[i]=x;
  }
}
// ボックス＝ミュラー法を用いる
void rand_gauss(float n, float *y) {
    float *alpha = malloc(sizeof(float)*n);
    float *beta = malloc(sizeof(float)*n);
    float sigma = sqrtf(2/n);
    rand_init(n,0,alpha); //yを[-1:1] の乱数で初期化
    // print(1,10,alpha);
    rand_init(n,rand(),beta); //yを[-1:1] の乱数で初期化
    // print(1,10,beta);
    int i;
    for(i=0;i<n;i++) {
      float z=sqrtf(-2.0*log(*(alpha+i))) * cos(2.0*M_PI* *(beta+i));
      *(y+i) = sigma*z;
      if(*(y+i)>=1) {
        *(y+i) = 0.9999;
      } else if (*(y+i)<=-1) {
        *(y+i) = -0.9999;
      }
    }
}

void shuffle(int n, int *x) {
  int i,j;
  srand(time(NULL)); //乱数の種を初期化
  for (i=0;i<n;i++) {
     j = rand()%n;
     x[i] = x[j];
  }
}

void init(int n, float x, float * o) {
// o[i] = x を実行 //全ての値をxで初期化
  int i;
  for(i=0;i<n;i++) {
    o[i] = x;
  }
}

void add(int n, float m, const float * x, float * o) {
// o[i] += x[i] を実行
  int i;
  for(i=0;i<n;i++) {
    o[i] += x[i] * m;
  }
}

void scale(int n, float x, float * o) {
// o[i] *= x を実行
  int i;
  for(i=0;i<n;i++) {
    o[i] *= x;
  }
}

void updata(int n, float m, const float * x, float * o) {
// o[i] += x[i] を実行
  int i;
  for(i=0;i<n;i++) {
    o[i] -= x[i] * m;
  }
}

void memory(int n, const float * x, float * o) {
  int i;
  for(i=0;i<n;i++) {
    o[i] = x[i];
  }
}

void backward6(const float *A1, const float *b1, const float *A2, const float *b2, const float *A3, const float *b3, const float *x, unsigned char t, float *dA1, float *db1, float *dA2 , float *db2, float *dA3, float *db3) {

  float *y1 = malloc(sizeof(float)*50);
  float *y2 = malloc(sizeof(float)*100);
  float *y3 = malloc(sizeof(float)*10);
  float *FC_in1 = malloc(sizeof(float)*784);
  float *FC_in2 = malloc(sizeof(float)*50);
  float *FC_in3 = malloc(sizeof(float)*100);
  float *ReLU_in1 = malloc(sizeof(float)*50);
  float *ReLU_in2 = malloc(sizeof(float)*100);


  memory(784,x,FC_in1); //FC1への入力を記憶
  fc(50, 784, x, A1, b1, y1); //FC1層
      //↓
  memory(50,y1,ReLU_in1); //ReLU1層の入力を記憶
  relu(50, y1, y1); //ReLU1層
      //↓
  memory(50,y1,FC_in2); //FC2への入力を記憶
  fc(100, 50, y1, A2, b2, y2); //FC2層
      //↓
  memory(100,y2,ReLU_in2); //ReLU2層の入力を記憶
  relu(100, y2, y2); //ReLU2層
      //↓
  memory(100,y2,FC_in3); //FC3層の入力を記憶
  fc(10, 100, y2, A3, b3, y3); //FC3層
      //↓
  softmax(10, y3, y3); //Softmax層
      //⇔逆伝搬
  // print(1,10,y3);
  softmaxwithloss_bwd(10, y3, t, y3); //ソフトマックス+損失関数
      // ↓ 出力 y(=dx) を FC3層の dy として入力
      //  (次数1,次数2,順入,逆入,初期値A3,dA3,db3,逆出)
  // print(1,10,y3);
  fc_bwd(10, 100, FC_in3, y3, A3, dA3, db3, FC_in3); //FC3
     //  ↓ 出力 FC_in3(=dx) をReLU2層の dy として入力
     //        (次数,順入,逆入,逆出)
  relu_bwd(100, ReLU_in2, FC_in3, ReLU_in2); //ReLU2
     //  ↓ 出力 ReLU_in2(=dx) をFC2層の dy として入力
     //   (次数1,次数2,順入,逆入,初期値A2,dA2,db2,逆出)
  fc_bwd(100, 50, FC_in2, ReLU_in2, A2, dA2, db2, FC_in2); //FC2
     //  ↓ 出力 FC_in2(=dx) をReLU1層の dy として入力
     //        (次数,順入,逆入,逆出)
  relu_bwd(50, ReLU_in1, FC_in2, ReLU_in1); //ReLU1
     //  ↓ 出力 ReLU_in1(=dx) をFC1層の dy として入力
     //   (次数1(右),次数2(左),順入,逆入,初期値A2,dA2,db2,逆出)
  fc_bwd(50, 784, FC_in1, ReLU_in1, A1, dA1, db1, FC_in1); //FC1
}

void save(const char *filename, int m, const float *x) {
  FILE *fp;
  // float inbuf[10];
  if((fp = fopen(filename, "wb+")) == NULL ) {
		printf("ファイルオープンエラー\n");
		exit(EXIT_FAILURE);
	}
  fwrite(x, sizeof(float), m, fp);
  fclose(fp);
}

void load(const char *filename, int m, float *x) {
  FILE *fp;
  if((fp = fopen(filename, "wb+")) == NULL ) {
		printf("ファイルオープンエラー\n");
		exit(EXIT_FAILURE);
	}
  fread(x, sizeof(float), m, fp);
  fclose(fp);
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

int main(int argc, char * argv[]) {
  //初期値の設定
  float * train_x = NULL;
  unsigned char * train_y = NULL;
  int train_count = -1;

  float * test_x = NULL;
  unsigned char * test_y = NULL;
  int test_count = -1;

  int width = -1;
  int height = -1;

  //訓練データとテストデータの読み込み
  load_mnist(&train_x, &train_y, &train_count,
             &test_x, &test_y, &test_count,
             &width, &height);

  //各パラメーターのメモリ容量の確保
  int *index = malloc(sizeof(int)*60000); //訓練データ用
  float *y = malloc(sizeof(float)*10); //テストデータの格納y

  float *A1 = malloc(sizeof(float)*784*50); //paramater A1
  float *b1 = malloc(sizeof(float)*50); //paramater b1
  float *A2 = malloc(sizeof(float)*50*100); //paramater A2
  float *b2 = malloc(sizeof(float)*100); //paramater b2
  float *A3 = malloc(sizeof(float)*100*10); //paramater A3
  float *b3 = malloc(sizeof(float)*10); //paramater b3

  float *dA1 = malloc(sizeof(float)*784*50); //勾配ベクトルdA1
  float *db1 = malloc(sizeof(float)*50); //勾配ベクトルdb1
  float *dA2 = malloc(sizeof(float)*50*100); //勾配ベクトルdA2
  float *db2 = malloc(sizeof(float)*100); //勾配ベクトルdb2
  float *dA3 = malloc(sizeof(float)*100*10); //勾配ベクトルdA3
  float *db3 = malloc(sizeof(float)*10); //勾配ベクトルdb3

  float *dAs1 = malloc(sizeof(float)*784*50); //ΣdA1
  float *dbs1 = malloc(sizeof(float)*50); //Σdb1
  float *dAs2 = malloc(sizeof(float)*50*100); //ΣdA2
  float *dbs2 = malloc(sizeof(float)*100); //Σdb2
  float *dAs3 = malloc(sizeof(float)*100*10); //ΣdA3
  float *dbs3 = malloc(sizeof(float)*10); //Σdb3
  // //A1~3,b1~3を-1~1に初期化
  // rand_init(784*50, A1);
  // rand_init(50, b1);
  // rand_init(50*100, A2);
  // rand_init(100, b2);
  // rand_init(100*10, A3);
  // rand_init(10, b3);

  // //重み初期値にHeの初期値を利用
  rand_gauss(784*50, A1); //(平均,次数,重み)
  rand_gauss(50, b1);
  rand_gauss(50*100, A2);
  rand_gauss(100, b2);
  rand_gauss(100*10, A3);
  rand_gauss(10, b3);


  int i,j,k;
  for(i=0;i<5;i++) { // (5)エポック回数(10回)繰り返す
    for(j=0;j<60000;j++) { //(5-a)
      index[j] = j;
    } //初期化
    shuffle(60000, index);
    for(j=0;j<600;j++) { //(5-b) 学習回数(600)回繰り返す
      //dAs1~3,dbs1~3を0で初期化 (5-b-i)
      init(784*50, 0, dAs1);
      init(50, 0, dbs1);
      init(50*100, 0, dAs2);
      init(100, 0, dbs2);
      init(100*10, 0, dAs3);
      init(10, 0, dbs3);
      for (k=0;k<100;k++) { //(5-b-ⅰ,ⅱ)
        //dA1~3,db1~3の導出
        backward6(A1, b1, A2, b2, A3, b3, train_x + 784*index[k], train_y[index[k]], dA1, db1, dA2, db2, dA3, db3);
        //da,dbを加える
        add(784*50,1,dA1,dAs1);
        add(50,1,db1,dbs1);
        add(50*100,1,dA2,dAs2);
        add(100,1,db2,dbs2);
        add(100*10,1,dA3,dAs3);
        add(10,1,db3,dbs3);
      }
      //平均勾配を得る(5-b-ⅳ) 全体をnで割る
      scale(784*50, 0.01, dAs1);
      scale(50, 0.01, dbs1);
      scale(50*100, 0.01, dAs2);
      scale(100, 0.01, dbs2);
      scale(100*10, 0.01, dAs3);
      scale(10, 0.01, dbs3);
      //重みパラメーターを勾配方向に更新する
      updata(784*50,0.01,dAs1,A1);
      updata(50,0.01,dbs1,b1);
      updata(50*100,0.01,dAs2,A2);
      updata(100,0.01,dbs2,b2);
      updata(100*10,0.01,dAs3,A3);
      updata(10,0.01,dbs3,b3);
    }
    //評価,過学習などの客観性の保護のため、定量的な評価はテストデータで行う

    int sum=0;
    float z=0;
    for(j=0; j<test_count; j++) {
      if(inference6(A1, b1, A2, b2, A3, b3, test_x + 784*j, y) == test_y[j]) {
        sum++;
      }
      z += cross_entropy_error(y, test_y[j]);
    }
    printf("(エポック%d) -------------------------------------------------------\n",i+1);
    printf("正解率 : %f%%\n", sum * 100.0 / test_count);
    printf("損失関数 : %f\n", z / test_count);
  }
  save(argv[1], 784*50, A1);
  save(argv[2], 50, b1);
  save(argv[3], 50*100, A2);
  save(argv[4], 100, b2);
  save(argv[5], 100*10, A3);
  save(argv[6], 10, b3);

  return 0;
}
