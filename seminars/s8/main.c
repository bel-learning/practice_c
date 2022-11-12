#include <stdio.h>
#include <stdlib.h>

char * getBoardInput(char *board, int *size, int *capacity, char ch)
{

    if (*size >= *capacity - 1)
    {
        (*capacity) = (*capacity) * 2;
        board = (char *)realloc(board, *capacity * sizeof(board[0]));
    }
    board[*size] = ch;
    (*size)++;
    return board;
}
void changeChar(char *board, int index)
{
    char neigh_char = board[index];
    if (neigh_char != '*')
    {
        if (neigh_char == '.')
        {
            board[index] = '1';
        }
        else
        {
            board[index] = neigh_char + 1;
        }
    }
}

void computeBoard(char *board, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (board[i * col + j] == '*')
            {
                // top

                if (i > 0)
                {
                    changeChar(board, (i-1)*col + j);
                }
                // down
                if (i < row - 1)
                {
                    changeChar(board, (i+1)*col + j);

                }
                // left
                if (j > 0)
                {
                    changeChar(board, (i)*col + j - 1);
                }
                // right
                if (j < col - 1)
                {
                    changeChar(board, (i)*col + j + 1);
                }
                // left top
                if(i > 0 && j > 0) {
                    changeChar(board, (i-1)*col + j - 1);
                }
                // right top
                if(i > 0 && j < col - 1) {
                    changeChar(board, (i-1)*col + j + 1);
                }
                // left bottom
                if(i < row - 1 && j > 0) {
                    changeChar(board, (i+1)*col + j - 1);
                }
                // right top
                if(i < row - 1 && j < col - 1) {
                    changeChar(board, (i+1)*col + j + 1);
                }
            }
        }
    }
}

int main()
{
    char *board = (char *)malloc((10 * 10) * sizeof(char));
    int col = 0;
    int row = 0;
    int colNum = 0;
    int capacity = 100;
    int size = 0;
    printf("Enter game board:\n");
    while (1)
    {
        char ch;
        int x = scanf("%c", &ch);
        if (x == EOF)
        {
            break;
        }
        if(ch == ' ') {
            continue;
        }
        if (ch == '\n')
        {
            if(col == 0) {
                continue;
            }
            row++;
            colNum = col;
            col = 0;
            continue;
        }
        else if(ch != '*' && ch != '.') {
            printf("Invalid input.\n");
            free(board);
            return 0;
        }
        board = getBoardInput(board, &size, &capacity, ch);
        col++;
    }
    // printf("%d %d\n", size, row*colNum);
    if(size != row*colNum) {
        printf("Invalid input.\n");
        free(board);
        return 0;
    }
    if(colNum == 0 || row == 0) {
        printf("Invalid input.\n");
        free(board);
        return 0;
    }
    computeBoard(board, row, colNum);
    printf("Filled board:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            printf("%c", board[i * colNum + j]);
        }
        printf("\n");
    }
    free(board);
    return 0;
}
