// #include <stdio.h>


// //文字列の基礎
// int main () {
//
//   char str[4];
//   str[0] = 'A'; //一文字はシングルクオーテーション
//   str[1] = 'B';
//   str[2] = 'C';
//   str[3] = '\0';
//
//   //末尾は\0で示される、これがないと文字列とみなされない
//
//   // //文字列の初期化
//   // char str[] = "ABC"; //特殊な形、文字列はダブルクオーテーション
//   // char str[] = {'A','B','C','\0'};
//   // char str[] = ""; //特殊な形
//
//
//   printf("str : %s\n", str);
//   printf("char : %c\n", str[3]);
//   return 0;
// }

// 文字列の走査
//
#include <stdio.h>

int main() {
  int len = 0;
  char str[128];
  printf("input a word: ");
  scanf("%s", str);
  while( str[len] ) {
    len++;
  }
  printf("length: %d", len);
 }
