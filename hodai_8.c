#include "nn.h"

void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dx) {
  int i;
  for(i=0;i<n;i++){
    *(dx+i) = *(y+i) - t;
  }
}

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
    if (*(x+i)<=0) {
      *(y+i)=0;
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

int inference3(const float *A, const float *b, const float *x, float *y) {
  fc(10, 784, x, A_784x10, b_784x10, y);
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
  float *y = malloc(sizeof(float)*10);


  int ans = inference3(A_784x10, b_784x10, train_x, y);
  printf("%d %d\n", ans, train_y[0]);
  print(1, 10, y);
  // int i,sum = 0;
  // unsigned char t = ans;
  // // for(i=0; i<test_count; i++) {
  // //   if(ans == test_y[i]) {
  // //     sum++;
  // //   }
  // // }
  // printf("%f%%\n", sum * 100.0 / test_count); //正解率
  softmaxwithloss_bwd(784, y, ans, y);
  return 0;
}
