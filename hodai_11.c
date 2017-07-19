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
} //y=10 式(1) ,この時の入力x(=748)はfc_inに記憶

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

// int inference3(float *y) {
//   float max = *y;
//   int i,num = 0;
//   for (i=1; i<10; i++) {
//     if (max < *(y+i)) {
//         num = i;
//     }
//   }
//   return num;
// }

// softmaxwithloss_bwd(10, y, t, y);
void softmaxwithloss_bwd(int m, const float *y, unsigned char t, float *dx) {
  int i;
  for(i=0;i<m;i++){
    if (i==t) {
      *(dx+i) = *(y+i) - t;
    } else {
      *(dx+i) = *(y+i);
    }
  }
}
//dxはm次元で勾配ベクトル, yの箱にはm次元のdxが入っている
//yにはdx(勾配ベクトル)が入っている

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
// //yにはdx(勾配ベクトル)がそのまま
// //relu_inには計算した、dxが入っている
//
// fc_bwd(10, 784, fc_in, y, A, dA, db, fc_in);
void fc_bwd(int m, int n, const float *x, const float *dy, const float *A, float *dA, float *db, float *dx) {
//   //dA(10*784)とdb(10)は空の箱
//
  int i,j;
  // dA = dy・x(T)
  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      *(dA+i*n+j) = *(dy+i) * *(x+j);
    }
  }
//   db = dy
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
  // for (i=0;i<n;i++) {
  //   for (j=0;j<m;j++) {
  //      B[n*i+j] = BT[i][j];
  //   }
  // } //一次元配列に戻す
  for (i=0;i<n;i++) {
    for (j=0;j<m;j++) {
      *(dx+i*n+j) += BT[i][j] * dy[j];
    }
  } //前から10個ずつ取っていく
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

void shuffle(int n, int *x) {
  int i,j;
  srand(time(NULL)); //乱数の種を初期化
  for (i=0;i<n;i++) {
     j = rand()%n;
     x[i] = x[j];
  }
}

void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dA, float *db) {
  int i;
  float *fc_in = malloc(sizeof(float)*784);
  float *relu_in = malloc(sizeof(float)*10);
  for (i=0;i<784;i++) {
    *(fc_in+i) = *(x+i);
  }
  fc(10, 784, x, A, b, y);
  //x(=dA)を入力,y(=Ax+b, サイズ10)を出力
  for (i=0;i<10;i++) {
    *(relu_in+i) = *(y+i);
  }
  //入力する y(10)をdbに記憶させておく
  relu(10, y, y);
  // //活性化させる y(=db)入力、yにそのまま出力
  softmax(10, y, y);
  //推論させる y 入力, y出力
  // int ans = inference3(y);
  softmaxwithloss_bwd(10, y, t, y);
  // //勾配ベクトル 今 y には dx が入っている
  // print(1, 10, relu_in);
  relu_bwd(10, relu_in, y, y);
  // // //(10, 入力(db), 現在のdx, 出力(dx)の箱)
  fc_bwd(10, 784, fc_in, y, A, dA, db, fc_in);
  // この時点で yにはdx
  // (10, 784, x, dx, A, b, 出力(dx)の箱)
  // for (i=0;i<784*10;i++) {
  //   *(A+i) = *(A+i) - 0.01 * *(dA+i);
  // }
  // for (i=0;i<10;i++) {
  //   *(b+i) = *(b+i) - 0.01 * *(db+i);
  // }
}

void rand_init(int n, float * o) {
// o[i] を [-1:1] の乱数で初期化
  int i;
  srand(time(NULL));
  for(i=0;i<n;i++) {
    o[i] = rand()%3-1;
  }
}

void check(int n, float * o) {
  int i;
  for(i=0;i<n;i++) {
    if((o[i]>10)||(o[i]<-10))
      o[i]=0;
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
  // float *y //ポインタ変数の宣言
  float *y = malloc(sizeof(float)*10);
  //mallocによりメモリアドレスを確保し、メモリ領域の先頭アドレスをポインタ変数に代入
  float *dA = malloc(sizeof(float)*784*10);
  float *A = malloc(sizeof(float)*784*10); //paramater A
  float *b = malloc(sizeof(float)*10);
  float *db1 = malloc(sizeof(float)*10);
  // float *db2 = malloc(sizeof(float)*10);
  // float *dbs = malloc(sizeof(float)*10);
  // float *dbs = malloc(sizeof(float)*10);
  int *index = malloc(sizeof(int)*60000); //train_count
  int j,k;
  rand_init(784*10, A); //Aを-1~1に初期化
  rand_init(10, b);
  for(j=0;j<60000;j++) { //(5-a)
    index[j] = j;
  } //初期化
  shuffle(60000, index);
  for (k=0;k<10;k++) {
    // for(i=0;i<10;i++){
    //   dbs[i] = 0;
    // }
    backward3(A, b, train_x + 784*index[k], train_y[index[k]], y, dA, db1);
    check(10,db1);
    // backward3(A, b, train_x + 784*index[k+4], train_y[index[k+4]], y, dA, db2);
    // for(i=0;i<10;i++){
    //   dbs[i] = db1[i]+db2[i];
    // }
    print(1,10, db1);
  }
    // print(1, 10, db2);
    // print(1, 10, dbs);
  // }
    // print(1, 10, dbs);


  return 0;
}
