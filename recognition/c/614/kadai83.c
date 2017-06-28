#include <stdio.h>
#include <math.h>

typedef struct {
  double x;
  double y;
  double s;
} vector2d;

double GetLength(vector2d *std) {
  return sqrt(((*std).x)*((*std).x)+((*std).y)*((*std).y));
}

void Scale(vector2d *std, double s) {
  ((*std).x) *= s;
  ((*std).y) *= s;
  printf("Result : %lf %lf\n", (*std).x,(*std).y);
}


int main() {
  double s;
  vector2d vec = {0, 0};
  printf("Input 2D Vector: ");
  scanf("%lf %lf", &vec.x, &vec.y);
  printf("Input scale value: ");
  scanf("%lf", &s);
  Scale(&vec, s);
  printf("Length: %lf\n", GetLength(&vec));
}
