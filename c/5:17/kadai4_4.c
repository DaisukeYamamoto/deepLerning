#include <stdio.h> // <stdio.h> は標準入出力
// #include <math.h> 平方根などの数学を利用
// #include <time.h> 乱数を利用
// #define 名前 数値 でマクロ変数を指定できる  


//大域変数として空の配列を用意
int a[]={}; //空の配列の用意の仕方（配列初期条件の設定）

//ユーザーからの入力を求める
int input() {
  int n;
  //int:整数 double,float:小数点(%f:printf,%lf:scanfで受ける),char:文字
  while (1) { //while(1) or for (;;)で無限ループ
    // do{   文    for or while() {
    //  }while()                 }  の使い分けに注意
    printf("n = "); //printfは%dとnで対応
    scanf("%d", &n); //scanfは%dと&nで対応
    if (n >= 0) {
      break;
    } else {
    printf("Invalid input => Input again\n");
    }
  }
  return n; //このままだとprintfが返されるので返り値を指定
}

//n乗の計算
int factorial(int n) { //引数（型名:名前）
  int i;
  int result = 1;
  if (n==0) { //比べるときのイコールは==で２本 ||:or &&:& !:not
    result = 1;
  } else {
    for ( i = n ; i > 0 ; i--) { //for(初期条件;終わり条件;繰返し動作)
      //i--でi=i-1
      result = result * i;
    }
  }
  return result;
}

//代入
int substitution(int r, int p) { //(引数1,引数2の形)
  a[r] = p;
  return 0;
}

//配列の値を表示
int display(int n, int r) {
  printf("perm(%d,%d) = %d\n",n,r,a[r]);
  return 0;
}

//実行部分
int main() {
  int n,r,p;
  n = input();
  if (n==0) {
    printf("perm(0,0) = 1\n");
  } else {
    for(r=0;r<=n;r++) {
      p = factorial(n) / factorial(n-r);
      substitution(r,p);
      display(n,r);
    }
  }
  return 0;
}

// 出力は gcc -Wall ファイル名.c -lm
