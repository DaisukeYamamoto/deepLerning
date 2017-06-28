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

void scale(int n, float x, float * o) {
  int i;
  for(i=1;i<=n;i++) {
    o[i-1] *= x;
  }
}

int main() {
  float y[6] = {1,1,2,3,5,8};
  print_oct(2,3,y,"y");
  scale(6, 1.5, y);
  print_oct(2,3,y,"y");
  return 0;
}
