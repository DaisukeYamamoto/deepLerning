#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[50], str2[50];
    int i, len;

    printf("input a word: ");
    scanf("%s", str1);

    len = strlen(str1);

    for (i = 0; i<len; i++)  {
        str2[i] = str1[i] + 1;
    }
    //終端にNULLを付加する
    str2[i] = '\0';
    printf("文字列は%sです\n", str2);

    return 0;
}
