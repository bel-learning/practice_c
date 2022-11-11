#include<stdio.h>
#include<stdlib.h>
int numbers[2501];
int prefixSums[2501];
int main() {
    printf("Input sequence:\n");
    int iter = 0;
    int n;
    while(1) {
        int x = scanf("%d", &n);
        if(x == EOF) {
            if(iter == 0) {
                printf("Invalid input.\n");
                return 0;
            }
            break;
        }
        if(x != 1) {
            printf("Invalid input.\n");
            return 0;
        }
       
        numbers[iter] = n;
        if(iter == 0) {
            prefixSums[iter] = n;
            iter++;
            continue;
        }
        prefixSums[iter] = prefixSums[iter-1] + n;
        iter++;
    }

    if(iter > 1999 || iter < 0) {
        printf("Invalid input.\n");
        return 0;
    }
    // printf("iter: %d\n", iter);
    // printf("numbers: ");

    // for(int i = 0; i < iter; i++) {
    //     printf("%d ", numbers[i]);
    // }
    // printf("\n");
    // printf("prefix sum: ");
    // for(int i = 0; i < iter; i++) {
    //     printf("%d ", prefixSums[i]);
    // }
    // printf("\n");
    // 6 numbers -> 21 elements of combinations of the sum 1..6 1..5 2..1 => 1 + 2 + 3 + 4 + 5 + 6

    int sumPos = iter*(iter+1)/2;
    int *sums = (int*)malloc(sumPos * sizeof(int));
    int highestElement = prefixSums[iter-1] + 1;
    int *table = (int*)malloc(highestElement * sizeof(int));

    int cnt = 0;
    int highestSum = prefixSums[iter-1] + 1;
// initialize table with zeros
    for(int i = 0; i < highestSum; i++) {
        table[i] = 0;
    }
    for(int i = 0; i < iter; i++) {
        for(int j = i+1; j < iter; j++) {
            if(j - 1 == i) {
                sums[cnt] = prefixSums[j];
            }
            if(i == 0 ) {
                sums[cnt] = prefixSums[j];
            }
            else {
                sums[cnt] = prefixSums[j]-prefixSums[i-1];
            }

            table[sums[cnt]]++;
            cnt++;
        }
    }

    // for(int i = 0; i < sumNum; i++) {
    //     printf("%d ", sums[i]);
    // }
    // printf("\n");

    // for(int i = 0; i < highestSum; i++) {
    //     printf("%d ", table[i]);
    // }
    // printf("\n");
    int result = 0;
    for(int i = 0; i < highestSum; i++) {
        if(table[i] > 1) {
            int n = table[i] - 1;
            result = result + (n * (n + 1) / 2);
        }
    }
    printf("Total pairs: %d\n", result);
    free(table);
    free(sums);
    return 1;
}
