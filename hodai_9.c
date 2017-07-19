#include "nn.h"

// void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dx) {
//   int i;
//   for(i=0;i<n;i++){
//     *(dx+i) = *(y+i) - t;
//   }
// }

// void memory(int n, const float * x, float * o) {
//   int i;
//   for(i=0;i<n;i++) {
//     o[i] = x[i];
//   }
// }

// void relu_bwd(int n, const float *x, const float *dy, float *dx) {
//   int i;
//   for(i=0;i<n;i++)
//     if (*(x+i)>0) {
//       *(dx+i) = *(dy+i);
//     } else if (*(x+i)<=0) {
//       *(dx+i) = 0;
//     }
// }
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

void softmax(int m, const float *x, float *y) {
  //入力 10→n 前回の出力y(=10)→x, y=出力
  int i;
  float z=0;
  float max = *x;
  for (i=1; i<m; i++) {
    if (max <= *(x+i)) {
      max = *(x+i);
    }
  }
  for(i=0; i<m; i++) {
    z += exp(*(x+i)-max);
  }
  for(i=0; i<m; i++) {
    *(y+i) = (exp(*(x+i)-max)) / z;
  }
}

int inference3(const float *A1, const float *b1,const float *A2, const float *b2, const float *A3, const float *b3, const float *x, float *y) {
  float *y1 = malloc(sizeof(float)*50);
  float *y2 = malloc(sizeof(float)*100);
  // float *y3 = malloc(sizeof(float)*10);
  // float *ReLU_in1 = malloc(sizeof(float)*50);
  // float *ReLU_in2 = malloc(sizeof(float)*100);
  // memory(784,x,FC_in1); //FC1への入力を記憶
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
  float max = y[0];
  int i,num = 0;
  for (i=1; i<10; i++) {
    if (max < y[i]) {
        num = i;
        max = y[i];
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

  int i,sum = 0;
  for(i=0;i<20;i++) {
    printf("%d %d\n", inference3(A1_784_50_100_10, b1_784_50_100_10, A2_784_50_100_10, b2_784_50_100_10, A3_784_50_100_10, b3_784_50_100_10, test_x+784*i,y), test_y[i]);
    print(1,10,y);
  }



  // unsigned char t = ans;
  for(i=0; i<test_count; i++) {
    if(inference3(A1_784_50_100_10, b1_784_50_100_10, A2_784_50_100_10, b2_784_50_100_10, A3_784_50_100_10, b3_784_50_100_10, test_x + 784*i, y) == test_y[i]) {
      sum++;
    }
  }
  printf("%f%%\n", sum * 100.0 / test_count);
  // softmaxwithloss_bwd(784, y, ans, y);
  // relu_bwd(784, y, y, y)
  return 0;
}
