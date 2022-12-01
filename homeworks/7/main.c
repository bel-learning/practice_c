#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int * arr;
    size_t size;
} ArrayWithSize;
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}
int op = 0;
int search(int size, int *w, int ws, int *n, int ns, int *e, int es, int *s, int ss, int a, int b, int aTurn) {
    op++;
    if(size == 0) {
        printf("a - %d b - %d\n", a,b);
        printf("Finished searching\n");
        return 0;
    }
    if(aTurn) {
        return 
        ((ws != 0) && search(size-1, w+1, ws-1, n, ns, e, es, s, ss, a + w[0], b, 0)) ||
        ((ns != 0) && search(size-1, w, ws, n+1, ns-1, e, es, s, ss, a + n[0], b, 0)) ||
        ((es != 0) && search(size-1, w, ws, n, ns, e+1, es-1, s, ss, a + e[0], b, 0)) ||
        ((ss != 0) && search(size-1, w, ws, n, ns, e, es, s+1, ss-1, a + s[0], b, 0));
    }
    else {
        return 
        ((ws != 0) && search(size-1, w+1, ws-1, n, ns, e, es, s, ss, a, b + w[0], 1)) ||
        ((ns != 0) && search(size-1, w, ws, n+1, ns-1, e, es, s, ss, a, b + n[0], 1)) ||
        ((es != 0) && search(size-1, w, ws, n, ns, e+1, es-1, s, ss, a, b + e[0], 1)) ||
        ((ss != 0) && search(size-1, w, ws, n, ns, e, es, s+1, ss-1, a, b + s[0], 1));
    }
}

int main() {
   
    ArrayWithSize * tokens = (ArrayWithSize *) malloc(4 * sizeof(*tokens));
   
    int w[] = {1,2,-4};
    int n[] = {9,1,1};
    int e[] = {3,5,-2};
    int s[] = {1,7};

    ArrayWithSize choices;
    choices.size = 4;
   
    size_t tokenSize = 11;
    int a = 0;
    int b = 0;
    search(tokenSize, w, 3, n, 3, e, 3, s, 2,  a, b, 1);
    printf("Operations: %d\n", op);
    // for(size_t i = 0; i < 10; i++) {
    //     free(tokens[i].arr);
    // }
    // free(tokens);
}
