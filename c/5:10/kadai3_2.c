#include <stdio.h>

int main () {
  int n,i,a;
  printf("n=");
  scanf("%d", &n);
  a = 1;
  i = 1;
  while ( i <= n ) {
    a = a * i;
    i++;
  }
  printf("answer＝%d\n", a);
}
