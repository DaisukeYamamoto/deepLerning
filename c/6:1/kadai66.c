#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// void print_oct(int m, int n, const float * x, const char * name) {
//   printf("%s1 = [", name);
//   int i,j,w;
//   w = 0;
//     for(i=1;i<=m;i++) {
//       for(j=1;j<=n;j++){
//         printf("%f ", x[j+w-1]);
//       }
//       w += n;
//       printf(";\n");
//     }
//   printf("];\n");
// }

void rand_init(int n, float * o) {
  int i;
  srand(time(NULL));
  for(i=1;i<=n;i++) {
    o[i-1] = (rand()%3) + (1*-1);
  }
}

int main() {
  float y[6];
  print_oct(2,3,y,"y");
  rand_init(6,y);
  print_oct(2,3,y,"y");
  return 0;
}
