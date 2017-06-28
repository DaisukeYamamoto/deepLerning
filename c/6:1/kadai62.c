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

int main() {
  float m[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
  print_oct(3,4,m,"m");
  return 0;
}
