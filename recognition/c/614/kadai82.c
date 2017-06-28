#include <stdio.h>
#include <math.h>

typedef struct {
  double x;
  double y;
} vector2d;

double GetLength(vector2d *std) {
  return sqrt(((*std).x)*((*std).x)+((*std).y)*((*std).y));
}

int main() {
  vector2d vec = {0, 0};
  printf("Input 2D Vector: ");
  scanf("%lf %lf", &vec.x, &vec.y);
  printf("Length: %lf\n", GetLength(&vec));
}
