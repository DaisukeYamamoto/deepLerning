#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
  int x,y;
  int y_range=3;
  int y_base=1;

  while(1) {
    printf("Your Input (0,2,5): ");
    scanf("%d", &x);
    srand(time(NULL));
    y = (rand() % y_range) + y_base;
    switch (y) {
      case 1 : y = 0;
      case 2 : y = 2;
      case 3 : y = 5;
    }


     if ((x == 0 && y ==2) || (x == 2 && y ==5) || (x == 5 && y ==0)) {
       printf("Comp:%d vs You:%d => You win.\n", y,x);
       break;
     } else if ( (x == 0 && y ==5) || (x == 2 && y ==0) || (x == 5 && y ==2)) {
       printf("Comp:%d vs You:%d => You lose.\n",y,x);
       break;
     } else if ( x == y ){
       printf("Comp:%d vs You:%d => Try again.\n",y,x);
     } else {
       printf("Invalid input => Try again.\n");
     }
  }

  return 0;
}
