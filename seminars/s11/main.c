#include <stdio.h>
#include <stdlib.h>
int cnt = 0;
void rec(int n, int k, char *arr, int index, int cons0, int cons1)
{
        cnt++;

    for (int i = 0; i < index; i++)
    {
        printf("%c", arr[i]);
        if (i == index - 1)
        {
            printf("\n");
        }
    }

    if (n == 0)
    {
        return;
    }
    if (cons0 < k)
    {
        arr[index] = '0';
        rec(n - 1, k, arr, index + 1, cons0 + 1, 0);
    }
    if (cons1 < k)
    {
        arr[index] = '1';
        rec(n - 1, k, arr, index + 1, 0, cons1 + 1);
    }
    
}

int main()
{
    printf("Number of digits:\n");
    int n, k;
    if(scanf("%d", &n) != 1 || n <= 0 || n > 64) {
        printf("Invalid input.\n");
        return 0;
    }
    printf("Max. run length:\n");
    if(scanf("%d", &k) != 1 || k <= 0){
        printf("Invalid input.\n");
        return 0;

    }
    char *arr = (char *)malloc(n * sizeof(char));
    int cons1 = 1;
    int cons0 = 0;

    arr[0] = '1';
    int index = 1;
    rec(n-1, k, arr, index, cons0, cons1);
    printf("Total: %d\n", cnt);
}
