#include <stdio.h>

int input() {
  int n;
  while (1) {
    printf("n = ");
    scanf("%d", &n);
    if (n >= 0) {
      break;
    } else {
    printf("Invalid input => Input again\n");
    }
  }
  return n;
}


int factorial(int n) {
  int a;
  if (n==0) {
    a = 1;
  } else {
    int i;
    a = 1;
    for ( i = n ; i > 0 ; i--) {
      a = a * i;
    }
  }
  return a;
}

int perm() {
  int n,r,p;
  n = input();
  for(r=0;r<=n;r++) {
    p = factorial(n) / factorial(n-r);
    printf("perm(%d,%d) = %d\n",n,r,p);
  }
  return 0;
}

int main() {
  perm();
}
