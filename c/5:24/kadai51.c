#include <stdio.h>

int factorial(int n, int r) { //引数（型名:名前）
  if ((r==0)||(n==r)||(r==1)) {
    return 1;
  } else {
    return (factorial(n-1,r-1)+factorial(n-1,r));
  }
}

int main(void) {
  int n,r;
  scanf("%d\n", &n);
  scanf("%d", &r);
  printf("%d\n", factorial(n,r));
  return 0;
}
