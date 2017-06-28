#include <stdio.h>

void minmax(int data[],int *min, int *max){ //アドレスの値を受け取る
  // date内のminとmaxを書き換える
  if (*min > *max) {
    int tmp = *max;
    *max = *min;
    *min = tmp;
    data[0] =
  }
}

int main() {
  int n,m,w;
  int data[];
  printf("input 1st integer");
  scanf("%d", &n);
  printf("input 2nd integer");
  scanf("%d", &m);
  printf("input 3rd integer");
  scanf("%d", &w);
  // int *pn //アドレス変数の宣言
  // pn = &n //pnにnのアドレスを渡す

  printf("input 1st integer : %d\n", n); //nの部屋の値を表示する
  printf("input 2nd integer : %d\n", m); //nの部屋の値を表示する
  printf("input 3rd integer : %d\n", w); //nの部屋の値を表示する
  minmax(data,&m,&w); //アドレスを渡して,,,
  minmax(date,&m,&w); //アドレスを渡して,,,
  printf("min: %d, max: %d", date[0],data[2]);
  return 0;
}
