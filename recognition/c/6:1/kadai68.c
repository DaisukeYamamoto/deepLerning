#include <stdio.h>


void fc(int m, int n, const float * x, const float * A, float * o) {
  int i,j,w;
  w = 0;
  for(i=1;i<=m;i++) {
    for(j=1;i<=n;i++) {
      w += x[i-1] * A[i-1];
    }
  o[i-1] = w + o[i-1];
  }
}


int main() {
  float A[6] = {1,2,3,4,5,6};
  float b[2] = {0.5, 0.25};
  float x[3] = {2,3,5};
  float o[2];
  fc(2,3,x,A,b,o);
  print_oct(2,3,A,"A");
  print_oct(2,1,b,"b");
  print_oct(3,1,x,"x");
  print_oct(2,1,o,"o");
  return 0;
}
