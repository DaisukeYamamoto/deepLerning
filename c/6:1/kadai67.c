#include <stdio.h>

void print_oct(int m, int n, const float * x, const char * name) {
  printf("%s1 = [", name);
  int i,j,w;
  w = 0;
    for(i=1;i<=m;i++) {
      for(j=1;j<=n;j++){
        printf("%f ", x[j+w-1]);
      }
      w += n;
      printf(";\n");
    }
  printf("];\n");
}

void mul(int m, int n, const float * x, const float * A, float * o) {
  int i,j;
  float w;
  w = 0;
  for(i=1;i<=m;i++)
    for(j=1;i<=n;i++) {
      w += x[i] * A[i];
    }
    o[i] = w;
}

int main() {
  float A[6] = {1,2,3,4,5,6};
  float x[3] = {2,3,5};
  float o[2];
  mul(2,3,x,A,o);
  print_oct(2,3,A,"A");
  print_oct(3,1,x,"x");
  print_oct(2,1,o,"o");
  return 0;
}
