#include <stdio.h>

int main(void) {
  char y = 'a';
  printf("%c %d %x\n",y ,y ,y);
  y = y + 1;
  printf("%c %d %x\n",y ,y ,y);
  return 0;
}
