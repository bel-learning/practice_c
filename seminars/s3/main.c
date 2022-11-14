#include<stdio.h>



int main(void) {
    char r,g,b;
    char pl, pr, c1,c2;
    int r1, r2, r3 = 0;
    printf("Type color in RGB format:\n");
    int x = scanf(" %c%c%c %c %d %c %d %c %d %c", &r, &g, &b, &pl, &r1, &c1, &r2, &c2 ,&r3, &pr);
    
    // printf("%c%c%c %c %c %c %c\n", r,g,b,pl, c1,c2, pr);
    if(x != 10 || c1 !=',' || c2 != ',' || pl != '(' || pr != ')') {
        printf("Invalid input.\n");
        return 0;
    }
    if(r != 'r' || g != 'g' || b != 'b') {
        printf("Invalid input.\n");
        return 0;
    }
    if(r1 < 0 || r1 > 255 || r2 < 0 || r2 > 255 || r3 < 0 || r3 > 255) {
        printf("Invalid input.\n");
        return 0;
    }
    char hex[7];
    
    hex[0] = '#';
}
