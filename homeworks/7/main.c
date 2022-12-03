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
    int answer[128][2];
} twoValue;
typedef struct {
    int arr[32];
    size_t size;
} tokenArr;
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}
int initialSizes[4];
int op = 0;
twoValue search(ArrayWithSize * tokens, size_t size, int a, int b, int aTurn, int ** answer, size_t ansI) {
    op++;
   
    twoValue ab;
    ab.a = a;
    ab.b = b;
    if(size == 0) {
        for(size_t i = 0; i < ansI; i++) {
            ab.answer[i][0] = answer[i][0];
            ab.answer[i][1] = answer[i][1];

            printf("%d %d\n", answer[i][0], answer[i][1]);
        }
        return ab;
        // return 0;
    }
    if(aTurn) {
        twoValue arr[4];
        int cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        max.a = INT32_MIN;
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                answer[ansI][0] = i;
                answer[ansI][1] = initialSizes[i]-tokens[i].size;

                tokens[i].size--;
                tokens[i].arr++;
                arr[cnt++] = search(tokens, size - 1, a + current, b, 0, answer, ansI+1);
                tokens[i].size++;
                tokens[i].arr--;
            }
        }
        for(size_t i = 0; i < cnt; i++) {
            if(max.a <= arr[i].a) {
                max = arr[i];
            }
        }
        return max;
    }
    else {
        twoValue arr[4];
        int cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        max.b = INT32_MIN;
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                answer[ansI][0] = i;
                answer[ansI][1] = initialSizes[i]-tokens[i].size;

                tokens[i].size--;
                tokens[i].arr++;
                arr[cnt++] = search(tokens, size - 1, a , b + current, 1, answer, ansI+1);
                tokens[i].size++;
                tokens[i].arr--;
            }
        }
        for(size_t i = 0; i < cnt; i++) {
            if(max.b <= arr[i].b) {
                max = arr[i];
            }
        }
        return max;
    }
}

int main() {
   
    ArrayWithSize * tokens = (ArrayWithSize *) malloc(4 * sizeof(*tokens));
    for(size_t i = 0; i < 4; i++) {
        tokens[i].arr = (int *) malloc(sizeof(int) * 10);
    }
    tokens[0].arr[0] = 1;
    tokens[0].arr[1] = 2;
    tokens[0].size = 2;
    
    tokens[1].arr[0] = 3;
    tokens[1].arr[1] = 5;
    tokens[1].size = 2;
    
    tokens[2].arr[0] = 9;
    tokens[2].arr[1] = 1;
    tokens[2].arr[2] = 1;
    tokens[2].arr[2] = 1;
    tokens[2].size = 4;

    tokens[3].arr[0] = 1;
    tokens[3].arr[1] = 7;
    tokens[3].size = 2;
    
    size_t tokenSize = 4+2+2+2;

    twoValue ab;
    int ** answer = (int **) malloc(128 * sizeof(*answer));
    for(size_t i = 0; i < 128; i++) {
        answer[i] = (int *) malloc(2 * sizeof(int));
    }
    size_t ansI = 0;
    initialSizes[0] = 2;
    initialSizes[1] = 2;
    initialSizes[2] = 4;
    initialSizes[3] = 2;

    ab = search(tokens, tokenSize, 0, 0, 1, answer, ansI);

    
    printf("Operations: %d\n", op);
    printf("last: %d %d\n", ab.a, ab.b);
    int a = 0, b = 0;
    for(size_t i = 0; i < tokenSize; i++) {
        if(i % 2) {
            a+= (tokens[ab.answer[i][0]].arr[ab.answer[i][1]]);
        }
        else {
            b+= (tokens[ab.answer[i][0]].arr[ab.answer[i][1]]);
        }
        printf("%d %d\n", ab.answer[i][0], ab.answer[i][1]);
    }
    printf("path check: %d %d\n", a, b);
    // for(size_t i = 0; i < 10; i++) {
    //     free(tokens[i].arr);
    // }
    
    // free(tokens);
}
