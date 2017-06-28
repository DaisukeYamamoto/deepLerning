#include <stdio.h>

int main(void) {
  float a=0;
  float b=0;
  double c=0;
  double d=0;
  int i;
  for (i=0;i<100000000;i++) {
    a = a + 0.00000001;
    c = c + 0.00000001;
  }
  b = 0.00000001*100000000;
  d = 0.00000001*100000000;
  printf("%f %f %lf %lf \n",a,b,c,d );
}

//float型では表現できる桁が7桁までゆえ
