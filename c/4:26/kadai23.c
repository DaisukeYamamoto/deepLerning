#include <stdio.h>
#include <math.h>

int main() {
  int a,b,c;
  printf("a =  ");
  scanf("%d", &a);
  printf("b =  ");
  scanf("%d", &b);
  printf("c =  ");
  scanf("%d", &c);
  double x1,x2;
  if (b*b-4*a*c >= 0) {
    printf("実数解を持つ");
    x1 = (-1*b+sqrt(b*b-4*a*c))/(2*a);
    x2 = (-1*b-sqrt(b*b-4*a*c))/(2*a);
    printf("%f\n", x1);
    printf("%f\n", x2);;
  } else {
    printf("虚数解を持つ");
    x1 = (-1*b)/(2*a);
    x2 = sqrt(b*b-4*a*c)/(2*a);
    printf("x1 = %f + %f", x1, x2);
    printf("x2 = %f - %f", x1, x2);
  }

  return 0;
}
