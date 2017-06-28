#include <stdio.h>
#include <stdlib.h>
#define N 8

int set(int data[], int n) {
  int i;
  for (i=0;i<n;i++) {
    data[i] = rand()%10000;
  }
  return 0;
}

void swap(int *a, int *b) { //渡されたアドレスを受けとり、そのアドレスに格納されている値を得る
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(int argc, char *argv[]) {
  FILE *fp;
  char *title;
  int n = atoi(argv[1]);
  title = argv[2];
  int data[n];
  set(data, n);
  int i,j;
  for(i=0;i<n-1;i++) {
    for(j=0; j<n-1; j++) {
      if( data[j] > data[j+1] ) {
        swap(&(data[j]), &(data[j+1]));
      }
    }
  };
  if((fp = fopen(title, "w")) == NULL)
    printf("File output: ERROR\n");
  else {
      for (i=0;i<n;i++) {
        fprintf(fp, "%d", data[i]);
      }
      fclose(fp);
  }
  // showarray(data);
  return 0;
}
