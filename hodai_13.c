

#include "nn.h"

float loss(const float * y, int t) {
  return 1*log(*(y+t)+1*exp(1)-7);
}

void shuffle(int n, int *x) {
  int i,j;
  srand(time(NULL)); //乱数の種を初期化
  for (i=0;i<n;i++) {
     j = rand()%n;
     x[i] = x[j];
  }
}

int main() {
  float * train_x = NULL;
  unsigned char * train_y = NULL;
  int train_count = -1;

  float * test_x = NULL;
  unsigned char * test_y = NULL;
  int test_count = -1;

  int width = -1;
  int height = -1;

  load_mnist(&train_x, &train_y, &train_count,
             &test_x, &test_y, &test_count,
             &width, &height);
  int i;
  int *index = malloc(sizeof(int)*train_count);
  for(i=0;i<train_count;i++) {
    index[i] = i;
  } //初期化
  shuffle(train_count, index);
  return 0;
}
