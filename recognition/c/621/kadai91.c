#include <stdio.h>
#include <stdlib.h>
#define N 10

int set(int data[], int n) {
  int i;
  for (i=0;i<n;i++) {
    data[i] = rand()%10000;
  }
  return 0;
}

int show(int data[], int n) {
  int i;
  printf("Data: ");
  for(i=0;i<n;i++) {
    printf("%d ", data[i]);
  }
  printf("\n");
  return 0;
}

int main() {
  int n = N;
  printf("N: ");
  scanf("%d",&n);
  int data[n];
  set(data, n);
  show(data, n);
  return 0;
}
