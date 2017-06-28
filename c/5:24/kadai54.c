#include <stdio.h>

int main(void) {
  int x,i,a;
  scanf("%d", &x);
  printf("%d(10)=", x);
  for(i=32;i>0;i--){
    if (((x>>i)&1) == 1) {
      a=1;
      printf("%d",a);
    } else {
      a=0;
      printf("%d",a);
    }
  }
  printf("(2)\n");
}
