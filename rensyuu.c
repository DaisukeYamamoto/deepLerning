#include "nn.h"


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

void load(const char *filename, int m, float *x) {
  FILE *fp;
  fp = fopen(filename, "r");
  if(!fp) {
    printf("File cannot open");
  }
  fread(x, sizeof(float), m, fp);
  fclose(fp);
}

int main(void)
{

  float *A1 = malloc(sizeof(float)*784*50); //paramater A1
  float *b1 = malloc(sizeof(float)*50); //paramater b1
  float *A2 = malloc(sizeof(float)*50*100); //paramater A2
  float *b2 = malloc(sizeof(float)*100); //paramater b2
  float *A3 = malloc(sizeof(float)*100*10); //paramater A3
  float *b3 = malloc(sizeof(float)*10); //paramater b3

  load("1.dat", 784*50, A1);
  load("2.dat", 50, b1);
  load("3.dat", 50*100, A2);
  load("4.dat", 100, b2);
  load("5.dat", 100*10, A3);
  load("6.dat", 10, b3);

  print(1,10,b3);
}
