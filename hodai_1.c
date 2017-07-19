#include "nn.h"

void print(int m, int n, const float *x) {
  int i,j,k;
  k = 0;
  for(i=0; i<m; i++) {
    for(j=0; j<n; j++) {
      printf("%.4f ", *(x+j+k));
    }
    printf("\n");
    k += n;
  }
}

int main() {
  print(1,10,b_784x10);
  //b_784x10はここではランダム、これは勾配法によって決まる
  return 0;
}
