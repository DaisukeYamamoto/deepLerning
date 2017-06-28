#include <stdio.h>
#define M 3
#define N 4
int main() {
  int a[M][N];
  int i, j;

  for (i=0; i<M; i++) {
    for(j=0; j<N; j++) {
      a[i][j] = 10*i+j;
    }
  }

  printf(" %d  %d  %d  %d \n", a[0][0],a[0][1],a[0][2],a[0][3]);
  printf("%d %d %d %d \n", a[1][0],a[1][1],a[1][2],a[1][3]);
  printf("%d %d %d %d \n", a[2][0],a[2][1],a[2][2],a[2][3]);

  return 0;
}
