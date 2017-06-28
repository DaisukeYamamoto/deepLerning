#include <stdio.h>


int main() {
  int x;
  printf("Type an integer: \n");
  scanf("%d", &x);

  if (x/3 == 0 || x/5 == 0) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  return 0;
}
