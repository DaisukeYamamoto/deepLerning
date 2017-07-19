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

int inference6(const float *A1, const float *b1,const float *A2, const float *b2, const float *A3, const float *b3, const float *x) {
  int i,num=0;
  float *y1 = malloc(sizeof(float)*50);
  float *y2 = malloc(sizeof(float)*100);
  float *y3 = malloc(sizeof(float)*10);
  fc(50, 784, x, A1, b1, y1); //FC1層
  // memory(50,y,ReLU_in1); //ReLU1層の入力を記憶
  relu(50, y1, y1); //ReLU1層
  // memory(50,y,FC_in2); //FC2への入力を記憶
  fc(100, 50, y1, A2, b2, y2); //FC2層
  // memory(100,y,ReLU_in2); //ReLU2層の入力を記憶
  relu(100, y2, y2); //ReLU2層
  // memory(100,y,FC_in3); //FC3層の入力を記憶
  fc(10, 100, y2, A3, b3, y3); //FC3層
  softmax(10, y3, y3); //Softmax層
  float max = y3[0];
  for (i=1; i<10; i++) {
    if (max < y3[i]) {
        num = i;
        max = y3[i];
    }
  }
  return num;
}

void load(const char *filename, int m, float *x) {
  FILE *fp;
  fp = fopen(filename, "r");
  if(!fp) {
    printf("File cannot open");
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

  float *A1 = malloc(sizeof(float)*784*50); //paramater A1
  float *b1 = malloc(sizeof(float)*50); //paramater b1
  float *A2 = malloc(sizeof(float)*50*100); //paramater A2
  float *b2 = malloc(sizeof(float)*100); //paramater b2
  float *A3 = malloc(sizeof(float)*100*10); //paramater A3
  float *b3 = malloc(sizeof(float)*10); //paramater b3
  float *x = load_mnist_bmp(argv[7]);

  load(argv[1], 784*50, A1);
  load(argv[2], 50, b1);
  load(argv[3], 50*100, A2);
  load(argv[4], 100, b2);
  load(argv[5], 100*10, A3);
  load(argv[6], 10, b3);

  int ans = inference6(A1, b1, A2, b2, A3, b3, x);
  printf("%d \n", ans);
  return 0;
}
