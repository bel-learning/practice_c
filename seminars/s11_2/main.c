#include<stdio.h>

int memo[10000];

int min (int a, int b) {
    if(a < b) {
        return a;
    } 
    else {
        return b;
    }
}

int rec(int coins[], size_t size, int current, int steps) {
    if(current < 0) {
        return __INT32_MAX__;
    }
    if(current == 0) {
        return steps;
    }
    if(memo[current] > 0) {
        return memo[current];
    }
    
    int minSteps = __INT32_MAX__;
    for(int i = 0; i < size; i++)
    {
        minSteps = min(minSteps, rec(coins, size, current - coins[i], steps + 1));
    }
    memo[current] = minSteps;
    
    // return rec(current - 5) || rec(current - 2) || rec(current - 1);
}

int intCmp(const int *a, const int *b) {
    return (*a < *b) - (*a > *b);
}
int main() {
    int coins[] = {1, 2, 5, 10, 20, 50, 5000, 2000, 1000, 500, 200, 100};
    for(size_t i = 0; i < 10000; i++) {
        memo[i] = 0;
    }
    // int amoints[100] = {1,2,3,4,5,6,7,8,9};
    int steps = 0;
    int target = 5555;
    // printf("size of array: %lu\n", sizeof(coins)/sizeof(coins[0]));
    printf("%d\n", rec(coins, sizeof(coins)/sizeof(coins[0]), target, steps));
}