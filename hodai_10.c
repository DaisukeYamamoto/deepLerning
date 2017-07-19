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

void softmax(int n, const float *x, float *y) {
  int i,z=0;
  float max = *x;
  for (i=1; i<n; i++) {
    if (max <= *(x+i)) {
      max = *(x+i);
    }
  }
  for(i=0; i<n; i++) {
    z += exp(*(x+i)+max);
  }
  for(i=0; i<n; i++) {
    *(y+i) = (exp(*(x+i)+max)) / z;
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

int inference3(float *y) {
  float max = *y;
  int i,num = 0;
  for (i=1; i<10; i++) {
    if (max < *(y+i)) {
        num = i;
    }
  }
  return num;
}

void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dx) {
  int i;
  for(i=0;i<n;i++){
    *(dx+i) = *(y+i) - t;
  }
}

void relu_bwd(int n, const float *x, const float *dy, float *dx) {
  int i;
  for(i=0;i<n;i++)
    if (*(x+i)>0) {
      *(dx+i) = *(dy+i);
    } else if (*(x+i)<=0) {
      *(dx+i) = 0;
    }
}

void fc_bwd(int n, int m, const float *x, const float *dy, const float * A, float *dA, float *db, float *dx) {
  int i,j;
  float B[10][784];
  for (i=0;i<10;i++) {
    for (j=0;j<784;j++) {
      B[i][j] = A[784*i+j];
    }
  }
  for (i=0;i<n;i++) {
    float z = 0;
    for (j=0;j<m;j++) {
      // *(*(A+i)+j) = *(*(A+j)+i); //Aを転置
      B[i][j] = B[j][i]; //転置行列
      z += B[i][j] * x[j];
    }
    *(dx+i) = z + *(db+i);
  } // dx = A(T) × dy

  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      *(dA+i*n+j) = *(dy+i) * *(x+j);
    } // dA = dy・x(T)

  *(db+i) = *(dy+i); // db = dy
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
  float *y = malloc(sizeof(float)*10);
  //計算(1)(2)(4)
  fc(10, 784, train_x, A_784x10, b_784x10, y);
  relu(10, y, y);
  softmax(10, y, y);
  print(1, 10, y);
  //推論(3層)
  int ans = inference3(y);
  printf("%d %d\n", ans, train_y[0]);
  //正解率(3層)
  int i,sum = 0;
  for(i=0; i<test_count; i++) {
    if(ans == test_y[i]) {
      sum++;
    }
  }
  printf("%f%%\n", sum * 100.0 / test_count);
  //------------

  softmaxwithloss_bwd(10, y, ans, y);
  relu_bwd(10, y, y, y);
  print(1, 10, y);
  // fc_bwd(10, 784, train_x, A_784x10, b_784x10, y)
  return 0;
}
