#include<stdio.h>
#include<math.h>

#define EPSILON 1e-10;

int main() {
    double x1 = 0.0,x2 = 0.0;
    char op, eq;
    double result = 0.0;
    printf("Type formula:\n");
    int x = scanf("%lg %c %lg %c", &x1, &op, &x2, &eq);
    if(x != 4 || !(op == '+' || op == '-' || op == '*' || op=='/') || eq !='=' || (op == '/' && x2 == 0)) {
        printf("Invalid input.\n");
        return 0;
    }

    switch(op) {
        case '+':
            result = x1 + x2;
            break;
        case '-':
            result = x1 - x2;
            break;
        case '/':
            result = x1 / x2;
            result = trunc(result);
            // 3.5 / 1.5 = 2
            break;
        case '*':
            result = x1 * x2;
            break;
    }
    
    printf("%g\n", result);
    return 0;
}
