#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
typedef struct {
    int * arr;
    size_t size;
} ArrayWithSize;
typedef struct {
    int a;
    int b;
} twoValue;
typedef struct {
    int arr[32];
    size_t size;
} tokenArr;
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

int op = 0;
twoValue search(ArrayWithSize * tokens, size_t size, int a, int b, int aTurn) {
    op++;
    printf("a: %d b: %d\n",a,b);
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < tokens[i].size; j++) {
            printf("%d ", tokens[i].arr[j]);
        }
        printf("\n");
    }
    twoValue ab;
    ab.a = a;
    ab.b = b;
    if(size == 0) {
        printf("Finished searching\n");
        printf("a: %d b: %d\n\n",a,b);
     
        return ab;
        // return 0;
    }
    if(aTurn) {
        twoValue arr[4];
        int cnt = 0;
        // copy tokens into tmp->
        tokenArr tmp[4];
        // token will always be size 4 as it has 4 directions;
        // for(size_t i = 0; i < 4; i++) {
        //     for(size_t j = 0; j < tmp[i].size; j++) {
        //         tmp[i].arr[j] = tokens[i].arr[j];
        //     }
        // }
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                tokens[i].size--;
                tokens[i].arr++;
                arr[cnt++] = search(tokens, size - 1, a + current, b, 0);
                tokens[i].size++;
                tokens[i].arr--;
            }
        }
        // twoValue maxA = arr[0];
        // for(size_t i = 0; i < cnt; i++) {
        //     if(maxA.a < arr[i].a) {
        //         maxA = arr[i];
        //     }
        // }
        free(tmp);
        return maxA;
    }
    else {
        
        twoValue arr[4];
        int cnt = 0;
        tokenArr tmp[4];
        // token will always be size 4 as it has 4 directions;
        for(size_t i = 0; i < 4; i++) {
            for(size_t j = 0; j < tmp[i].size; j++) {
                tmp[i].arr[j] = tokens[i].arr[j];
            }
        }
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tmp[i].arr[0]; 
                &(tmp[i].arr[0])++;
                arr[cnt++] = search(tmp, size - 1, a , b + current, 1);
            }
        }
        twoValue maxB = arr[0];
        for(size_t i = 0; i < cnt; i++) {
            if(maxB.b < arr[i].b) {
                maxB = arr[i];
            }
        }
        free(tmp);
        return maxB;
    }
}

int main() {
   
    ArrayWithSize * tokens = (ArrayWithSize *) malloc(4 * sizeof(*tokens));
    for(size_t i = 0; i < 4; i++) {
        tokens[i].arr = (int *) malloc(sizeof(int) * 10);
    }
    tokens[0].arr[0] = 1;
    tokens[0].arr[1] = 2;
    tokens[0].arr[2] = -4;
    tokens[0].size = 3;
    tokens[1].arr[0] = 9;
    tokens[1].arr[1] = 1;
    tokens[1].arr[2] = 1;
    tokens[1].size = 3;
    tokens[2].arr[0] = 3;
    tokens[2].arr[1] = 5;
    tokens[2].arr[2] = -2;
    tokens[2].size = 3;
    tokens[3].arr[0] = 1;
    tokens[3].arr[1] = 7;
    tokens[3].size = 2;
    
    size_t tokenSize = 3+3+3+2;

    twoValue ab;
    ab = search(tokens, tokenSize, 0, 0, 1);

    
    printf("Operations: %d\n", op);
    printf("last: %d %d\n", ab.a, ab.b);
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < tokens[i].size; j++) {
            printf("%d ", tokens[i].arr[j]);
        }
        printf("\n");
    }
    // for(size_t i = 0; i < 10; i++) {
    //     free(tokens[i].arr);
    // }
    
    // free(tokens);
}
