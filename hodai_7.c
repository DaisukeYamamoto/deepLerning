#include "nn.h"

// void fc(int m, int n, const float *x, const float *A, const float *b, float *y) {
//   int i,j,k;
//   k = 0;
//   for(i=0; i<m; i++) {
//     float z = 0;
//     for(j=0; j<n; j++) {
//       z += *(A+j+k) * *(x+j);
//     }
//     *(y+i) = z + *(b+i);
//     k += n;
//   }
// }
//
// void relu(int n, const float *x, float *y) {
//   int i;
//   for(i=0; i<n; i++) {
//     if (*(x+i)>0) {
//       *(y+i) = *(x+i);
//     } else {
//       *(y+i) = 0;
//     }
//   }
// }
//
// void softmax(int n, const float *x, float *y) {
//   int i,z=0;
//   float max = *x;
//   for (i=1; i<n; i++) {
//     if (max <= *(x+i)) {
//       max = *(x+i);
//     }
//   }
//   for(i=0; i<n; i++) {
//     z += exp(*(x+i)+max);
//   }
//   for(i=0; i<n; i++) {
//     *(y+i) = (exp(*(x+i)+max)) / z;
//   }
// }

// int inference3(const float *A, const float *b, const float *x, float *y) {
//   fc(10, 784, x, A_784x10, b_784x10, y);
//   relu(10, y, y);
//   softmax(10, y, y);
//   float max = *y;
//   int i,num = 0;
//   for (i=1; i<10; i++) {
//     if (max < *(y+i)) {
//         num = i;
//     }
//   }
//   return num;
// }

int inference3(const float *A, const float *b, const float *x) {

    float *y = malloc(sizeof(float)*10);
    //fc
    int i,j,k=0;
    for(i=0; i<10; i++) {
      float z = 0;
      for(j=0; j<784; j++) {
        z += *(A+j+k) * *(x+j);
      }
      *(y+i) = z + *(b+i);
      k += 784;
    }
    //relu
    for(i=0; i<10; i++) {
      if (*(y+i)>0) {
        *(y+i) = *(y+i);
      } else if(*(y+i)<=0) {
        *(y+i) = 0;
      }
    }

    //softmax関数
    float z=0;
    float ma = *y;
    for (i=1; i<10; i++) {
      if (ma <= *(y+i)) {
        ma = *(y+i);
      }
    }
    for(i=0; i<10; i++) {
      z += exp(*(y+i)+ma);
    }
    for(i=0; i<10; i++) {
      *(y+i) = (exp(*(y+i)+ma)) / z;
    }

    //最大添字を出力
    float max = *y;
    int num = 0;
    for (i=1; i<10; i++) {
      if (max < *(y+i)) {
          num = i;
          max = *(y+i);
      }
    }
    return num;
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

  int i,sum = 0;
  for(i=0; i<test_count; i++) {
    if(inference3(A_784x10, b_784x10, test_x +i*width*height) == test_y[i]) {
      sum++;
    }
  }
  printf("%f%%\n", sum * 100.0 / test_count);
  return 0;
}
