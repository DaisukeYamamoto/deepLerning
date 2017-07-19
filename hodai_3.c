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
}

void relu(int n, const float *x, float *y) {
  int i;
  for(i=0; i<n; i++) {
    if (*(x+i)>0) {
      *(y+i) = *(x+i);
    } else if (*(x+i)<=0) {
      *(y+i) = 0;
    }
  }
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

  // これ以降，３層NNの係数 A_784x10 および b_784x10 と，
  // 訓練データ train_x[0]～train_x[train_count-1], train_y[0]～train_x[train_count-1],
  // テストデータ test_x[0]～test_x[test_count-1], test_y[0]～test_y[test_count-1],
  // を使用することができる．

  float *y = malloc(sizeof(float)*10);
  fc(10, 784, train_x+784*8, A_784x10, b_784x10, y);
  print(1, 10, y);
  relu(10, y, y);
  print(1, 10, y);
  return 0;
}
