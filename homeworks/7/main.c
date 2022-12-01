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
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

int op = 0;
twoValue search(int size, int *w, int ws, int *n, int ns, int *e, int es, int *s, int ss, int a, int b, int aTurn) {
    op++;
    printf("a: %d b: %d\n",a,b);
    twoValue ab;
    ab.a = a;
    ab.b = b;
    if(size == 0) {
        printf("Finished searching\n");
        printf("a: %d b: %d\n\n",a,b);
        ab.a = a;
        ab.b = b;
        return ab;
        // return 0;
    }
    if(aTurn) {
        twoValue arr[4];
        int cnt = 0;

        if(ws != 0) {
            arr[cnt++] = search(size-1, w+1, ws-1, n, ns, e, es, s, ss, a + w[0],b, 0);
        }
        if(ns != 0) {
            arr[cnt++] = search(size-1, w, ws, n+1, ns-1, e, es, s, ss, a + n[0],b, 0);
        }
        if(es != 0) {
            arr[cnt++] = search(size-1, w, ws, n, ns, e + 1, es - 1, s, ss, a + e[0],b, 0);
        }
        if(ss != 0) {
            arr[cnt++] = search(size-1, w, ws, n, ns, e, es, s + 1, ss - 1, a + s[0],b, 0);
        }
        twoValue maxA = arr[0];
        for(size_t i = 0; i < cnt; i++) {
            if(maxA.a < arr[i].a) {
                maxA = arr[i];
            }
        }
        
        return maxA;
    }
    else {
        
        twoValue arr[4];
        int cnt = 0;
        if(ws != 0) {
            arr[cnt++] = search(size-1, w+1, ws-1, n, ns, e, es, s, ss, a ,b + w[0], 1);
        }
        if(ns != 0) {
            arr[cnt++] = search(size-1, w, ws, n+1, ns-1, e, es, s, ss, a ,b + n[0], 1);
        }
        if(es != 0) {
            arr[cnt++] = search(size-1, w, ws, n, ns, e + 1, es - 1, s, ss, a ,b + e[0], 1);
        }
        if(ss != 0) {
            arr[cnt++] =  search(size-1, w, ws, n, ns, e, es, s + 1, ss - 1, a ,b + s[0], 1);
        }
        twoValue maxB = arr[0];
        for(size_t i = 0; i < cnt; i++) {
            if(maxB.b < arr[i].b) {
                maxB = arr[i];
            }
        }
   
        return maxB;
    }
}

int main() {
   
    ArrayWithSize * tokens = (ArrayWithSize *) malloc(4 * sizeof(*tokens));
    printf("Tokens:\n");
    int w[] = {1, 2, -4, 1, 5};
    size_t wi = 0;
    int n[] = {9,1,1};
    size_t ni = 0;
    int e[] = {3,5,-2};
    size_t ei = 0;
    int s[] = {1,7};
    size_t si = 0;
    // while() {
    //     char * str;
    //     size_t size;
    //     if(getline(&str, &size, stdin) != EOF) {
    //         if(*str == ' ') 
    //         {
    //             str++;
    //             continue;
    //         }

    //         if(*str == 'N' || *str == 'W' || *str == 'E' || *str == 'S') {
    //             // read input
    //             if(*str == 'N') {
    //                 bool colon, braces1, braces2;

    //                 while(*str) {
    //                     if(*str == ' ') 
    //                     {
    //                         str++;
    //                         continue;
    //                     }
    //                     if(*str == ':') {
    //                         colon = true;
    //                         str++;
    //                         continue;
    //                     }   
    //                     if(*str == '{') {
    //                         braces1 = true;
    //                         str++;
    //                         continue;
    //                     }
    //                     if(isdigit(*str)) {
    //                         // hopefully number won't be higher than 100 digits lmao
    //                         char * numStr = (char *) malloc(100);
    //                         size_t cnt = 0;
    //                         while(isdigit(*str)) {
    //                             numStr[cnt] = *str;
    //                             str++;
    //                         }
    //                         if(*str != ',') {
    //                             // throw error
    //                         }
    //                         int num = atoi(numStr);
    //                         n[ni] = num;
    //                         free(numStr);
    //                     }
    //                     if(*str == '}') {
    //                         break;
    //                     }
    //                 }

    //             }
    //         }
    //     }
    // }
    

    size_t tokenSize = 5+3+3+2;
    twoValue ab;
    ab = search(tokenSize, w, 5, n, 3, e, 3, s, 2, 0, 0, 1);

    printf("Operations: %d\n", op);
    printf("last: %d %d\n", ab.a, ab.b);
    // for(size_t i = 0; i < 10; i++) {
    //     free(tokens[i].arr);
    // }
    // free(tokens);
}
