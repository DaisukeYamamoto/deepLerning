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

/* 配列の中身を表示 */
void showarray(int data[], int n) {
  int i;
  printf("Data: ");
  for (i=0; i<n; i++) {
    printf("%d ", data[i]);
  }
  printf("\n");
}

/* 値の入れ替え */
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  int n = N;
  printf("N: ");
  scanf("%d",&n);
  int data[n];
  set(data, n);
  show(data, n);
  int i,j;
  for(i=0;i<n-1;i++) {
    for(j=0; j<n-1; j++) {
      /* 1つ前より小さければ入れ替える */
      if( data[j] > data[j+1] ) {
        swap(&(data[j]), &(data[j+1]));
      }
      /* 配列の値を表示 */
    }
  }
  showarray(data, n);
  return 0;
}
