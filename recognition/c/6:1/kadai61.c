#include <stdio.h>

void print(int m, int n, const float * x) {
  int i,j,w;
  w = 0;
    for(i=1;i<=m;i++) {
      for(j=1;j<=n;j++){
        printf("%f ", x[j+w-1]);
      }
      w += n;
      printf("\n");
    }
}

int main() {
  float m[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
  print(3,4,m);
  return 0;
}
