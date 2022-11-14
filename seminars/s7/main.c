#include<stdio.h>
#include<math.h>


int main() {
    int parties;
    printf("Number of parties:\n");
    int x1 = scanf("%d", &parties);
    if(x1 != 1 || parties < 2 || parties > 26) {
        printf("Invalid input.\n");
        return 0;
    }
    int arr[26];
    for(int i = 0; i < parties; i++) {
        arr[i] = -1;
    }
    printf("Parties and votes:\n");
    for(int i = 0; i < parties; i++) {
        char ch;
        int el;
        int x2 = scanf(" %c %d", &ch, &el);
        if(x2 != 2 || ch < 65 || ch > 65 + parties || el <= 0) {
            printf("Invalid input.\n");
            return 0;
        }
        if(arr[ch-65] < 0) {
            arr[ch-65]=el;
        }
        else {
            printf("Invalid input.\n");
            return 0;
        }
    }
    for(int i = 0; i < parties; i++) {
        if(arr[i] < 0) {
            printf("Invalid input.\n");
            return 0;
        }
    }
    printf("Number of miners:\n");
    int miners;
    int x3 =scanf("%d", &miners);
    if(x3 != 1 || miners <= 0) {
        printf("Invalid input.\n");
        return 0;
    }
    double table[26];
    int positions[26];
    for(int i = 0; i < parties; i++) {
        positions[i] = 0;
    }
    if(miners < parties) {
        // if all the parties have sum vote
        int same = 1;
        for(int i = 0; i < parties; i++) {
            if(arr[0] != arr[i]) {
                same = 0;
            }
        }
        if(same) {
            printf("No solution.\n");
            return 0;
        }
    }
    

    for(int i = 0; i < miners; i++) {
        if(i == 0 ) {
            for(int j = 0; j < parties; j++) {
                table[j] = (arr[j] / 1.42 ) ;
                continue;
            }
        }
        double max = table[0];
        int maxIndex = 0;
        for(int j = 1; j < parties; j++) {
            if(max < table[j]) {
                max = table[j];
                maxIndex = j;
            } 
            else if(max == table[j]) {
                if(miners - i < 2) {
                    printf("No solution.\n");
                    return 0;
                }
            }
        }
        positions[maxIndex]++;
        table[maxIndex] = (double)arr[maxIndex] / (1 + positions[maxIndex])  ;
        // for(int j = 0; j < parties; j++) {
        //     printf("%.10f ", table[j]);
        //     printf("%d ", positions[j]);
        // }
        // printf("\n");
    }

    printf("Assigned positions:\n");
    for(int i = 0; i < parties; i++) {
        printf("%c: %d\n", i+65, positions[i]);
    }
    return 0;
}
