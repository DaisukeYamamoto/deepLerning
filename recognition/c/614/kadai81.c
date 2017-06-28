
#include <stdio.h>

/* 元の配列（6個） */
int ar[] = {64, 30, 8, 87, 45, 13};

/* 配列の中身を表示 */
void showarray(int ary[]) {
  int i;
  for (i=0; i<6; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}

/* 値の入れ替え */
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


int main(void)
{
  int i, j, n;
  n = 5;
  /* 外側のループ -- 1巡ごとに対象が減っていく */
  for(i=0;i<5;i++) {
    printf("loop%d: ", i+1);

    /* 内側のループ -- 最後尾から比較 */
    for(j=0; j<n; j++) {
      /* 1つ前より小さければ入れ替える */
      if( ar[j] > ar[j+1] ) {
        swap(&(ar[j]), &(ar[j+1]));
      }
      /* 配列の値を表示 */
    }
    showarray(ar);
    n--;
  }
  return 0;
}
