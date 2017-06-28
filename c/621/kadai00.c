#include <stdio.h>

void swap(int p[]) { //その１
  int temp = p[0];
  p[0] = p[1];
  p[1] = temp;
}

void swap(int p[]) { //その２
  int temp = *p;
  *p = *(p+1);
  *(p+1) = temp;
}

void swap(int *p) { //その３
  int temp = p[0]; //p[0] = *p、p[i] = *(p+1)
  p[0] = p[1];
  p[1] = temp;
}

int main() {
  int n[2];
  printf("input A:");
  scanf("%d" ,&n[0]);
  printf("input B:");
  scanf("%d" ,&n[1]);

  swap(n);

  printf("A: %d\n", n[0]);
  printf("B: %d\n", n[1]);

  return 0;
}
