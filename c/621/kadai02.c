#include <stdio.h>

int main() {
  char str[2][128]; //00 01 … 0128, 10 11 … 1128
  printf("Enter your first name: ");
  scanf("%s", str[0]);
  printf("Enter your last name: ");
  scanf("%s", str[1]);

  printf("hello, %s %s\n", str[0], str[1]);
  return 0;
}
