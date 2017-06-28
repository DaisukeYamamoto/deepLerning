#include <stdio.h>

int main() {
  FILE *fp = NULL;
  char str[128];
  fp = fopen("test.txt", "r");
  if(!fp) {
    printf("File cannot open\n");
    return 0;
  }
  while ( fgets(str, 128, fp) )
    fp = fopen("test2.txt", "w");
    fputs(str, fp);
    fclose(fp);
  fclose(fp);
}
