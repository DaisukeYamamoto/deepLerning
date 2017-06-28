#include <stdio.h>

void inc(int *pn){ //アドレスの値を受け取る
  //ここでpnの部屋の値を書き換えておく
  *pn = *pn + 1; //部屋の値を書き換える
}

int main() {
  int n = 0;
  printf("input a digit: ");
  scanf("%d", &n);
  // int *pn //アドレス変数の宣言
  // pn = &n //pnにnのアドレスを渡す
  inc(&n); //アドレスを渡して,,,
  printf("output: %d\n", n); //nの部屋の値を表示する
  return 0;
}
