#include <stdio.h>

int main () {
  int i,a,n;
  printf("n=");
  scanf("%d", &n);
  a = 1;
  for ( i = n ; i > 0 ; i--) {
    a = a * i;
  }
  printf("answer＝%d\n", a);
}
