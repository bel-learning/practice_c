#include <stdio.h>
#include <stdlib.h>

void getBoardInput(char *board, int *size, int *capacity, char ch)
{
    if (*size >= *capacity)
    {
        *capacity = *capacity * 2;
        board = (char *)realloc(board, *capacity * sizeof(char));
    }
    board[*size] = ch;
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
                    char neigh_char = board[(i - 1) * col + j];
                    if (neigh_char != '*')
                    {
                        if (neigh_char == '.')
                        {
                            board[(i - 1) * col + j - 1] = '1';
                        }
                        else
                        {
                            board[(i - 1) * col + j - 1] = neigh_char + 1;
                        }
                    }
                }
                // down
                if (i < row - 1)
                {
                    char neigh_char = board[(i + 1) * col + j];
                    if (neigh_char != '*')
                    {
                        if (neigh_char == '.')
                        {
                            board[(i + 1) * col + j - 1] = '1';
                        }
                        else
                        {
                            board[(i + 1) * col + j - 1] = neigh_char + 1;
                        }
                    }
                }
                // left
                if (j > 0)
                {
                    char neigh_char = board[i * col + j - 1];
                    if (neigh_char != '*')
                    {
                        if (neigh_char == '.')
                        {
                            board[i * col + j - 1] = '1';
                        }
                        else
                        {
                            board[i * col + j - 1] = neigh_char + 1;
                        }
                    }
                }
                // right
                if (j < col - 1)
                {
                    char neigh_char = board[i * col + j + 1];
                    if (neigh_char != '*')
                    {
                        if (neigh_char == '.')
                        {
                            board[i * col + j + 1] = '1';
                        }
                        else
                        {
                            board[i * col + j + 1] = neigh_char + 1;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    char *board = (char *)malloc((100 * 100) * sizeof(char));
    int col = 0;
    int row = 0;
    int colNum = 0;
    int capacity = 10000;
    int size = 0;
    printf("Enter game board:\n");
    while (1)
    {
        char ch;
        int x = scanf("%c", &ch);
        if (ch == '\n')
        {
            row++;
            colNum = col;
            col = 0;
            continue;
        }
        if (x == EOF)
        {
            break;
        }
        size = row * colNum + col;
        getBoardInput(board, &size, &capacity, ch);
        col++;
    }

    printf("row: %d col: %d\n", row, colNum);
    computeBoard(board, row + 1, colNum);
    for (int i = 0; i < row + 1; i++)
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