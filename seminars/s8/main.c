#include<stdio.h>
#include<stdlib.h>

void getBoardInput(char * board, int * size, int *capacity, char ch) {
    if(*size >= *capacity) {
            *capacity = *capacity * 2;
            board = (char *) realloc(board, *capacity * sizeof(char));
        }
    board[*size] = ch;
}


int main () {
    char * board = (char *) malloc((100*100) * sizeof(char));
    int col = 0;
    int row = 0;
    int colNum = 0;
    int capacity = 10000;
    int size = 0;
    printf("Enter game board:\n");
    while(1) {
        char ch;
        int x = scanf("%c", &ch);
        if(ch == '\n') {
            row++;
            colNum = col;
            col = 0;
            continue;
        }
        if(x == EOF) {
            break;
        }
        size = row * colNum + col;
        getBoardInput(board, &size, &capacity, ch);
        col++;

    }

    printf("row: %d col: %d\n", row, colNum);
    // computeBoard()
    for(int i = 0; i < row + 1; i++) {
        for(int j =0; j < colNum; j++) {
            printf("%c", board[i*colNum+j]);
        }
        printf("\n");
    }
    free(board);
    return 0;
}