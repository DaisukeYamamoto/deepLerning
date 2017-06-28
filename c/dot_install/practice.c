// 三項演算子
//
// if () {
// // returnA
// } else {
// // returnB
// } を一文で
//
// 返り値 = (条件) ? A : B;
//
// return (a>=b) ? a : b;

◯ポインタの基礎

メモリ(記憶領域):アドレスを格納するための変数
& : アドレス演算子
* : 間接演算子

int main(void) {
  int a;
  a = 10; //aの値

  int *pa //ポインタ変数の宣言、決まり文句
  pa = &a //アドレスの代入,アドレス演算子

  printf("%d\n", *pa)
  //*pa アドレスが指し示す値を取ってくる、間接演算子

  return 0;
}

◯ポインタのいいところ : メモリの節約

<ポインタを使わずに>

int main(void) {
  long a = 1000;
  f(a);
}

void f(long a) {
  a += 100;
  printf("%ld\n", a);
}

<ポインタを使って> 12個で済む

int main(void) {
  long a = 1000;
  f(&a); // &aでaのアドレスを示す

  return 0;
}

void f(long *pa) {
  //*pa でポインタ変数の宣言、ここではアドレスを受け取っている [型 *変数]でアドレスを受け取る。ポインタ変数は4つまでしか領域を取らない
  *pa += *pa 100;
  printf("%ld\n", *pa);
}

◯値渡しと参照渡しについて

値渡し
参照渡し

int main(void) {
  int a = 10;
  int b = 5;
  swap(&a, &b);
//このままだと返り値１つなので、実現できない
//アドレスを入れ替えることにより実現、返り値は用いない
  printf("a:%d, b:%d\n", a, b);
  return 0;
}

void swap(int *pa, int *pb) {
  int tmp;
  tmp = *pa;
  *pa = *pb;
  *pb = tmp;
  //アドレスを入れ替える
}

<おまけ>

◯関数の書き方

返り値の型 関数名(引数, ...) {
  処理；
  return 返り値;
}

void : 返り値、引数がないときはvoid!

一番初めにmain関数を見る

int main(void) {

  return 0; これは慣習、正常終了を伝える
}

基本はmain関数の上に全ての関数を書くが、下に書くときは、プロトタイプ宣言を行う。

◯配列

宣言
 int sales[配列数]
初期値の代入
 int sales2[3]={200,222,234}
文字列の配列 : charの配列(※ 終端は「\0」)

char s[] = {"a","b","c","\0"｝
char s[4] ="abc";
%cで受ける
