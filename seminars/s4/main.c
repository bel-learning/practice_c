#include <stdio.h>

int main(void)
{
    int size, width;
    printf("Enter chessboard size:\n");
    int x1 = scanf("%d", &size);
    if(x1 == 0 || size <= 0) {
        printf("Invalid input.\n");
        return 0;
    }
    printf("Enter field width:\n");
    int x2 = scanf("%d", &width);
     if(x2 == 0 || width <= 0) {
        printf("Invalid input.\n");
        return 0;
    }
    int last = size * width + 2;
   

    for (int i = 0; i < size + 2; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < last; j++)
            {
                if (j == 0)
                {
                    printf("+");
                }
                else if (j > 0 && j < last - 1)
                {
                    printf("-");
                }
                else
                {
                    printf("+");
                }
            }
            printf("\n");
        }
        else if (i == size + 1)
        {
            for (int j = 0; j < last; j++)
            {
                if (j == 0)
                {
                    printf("+");
                }
                else if (j > 0 && j < last - 1)
                {
                    printf("-");
                }
                else
                {
                    printf("+");
                }
            }
            printf("\n");
        }
        else
        {
            for (int p = 0; p < width; p++)
            {
                for (int j = 0; j < size + 2; j++)
                {
                    if (j == 0)
                    {
                        printf("|");
                    }
                    else if (j == size + 1)
                    {
                        printf("|");
                    }
                    else
                    {
                        if ((i + j) % 2 == 0)
                        {
                            for (int k = 0; k < width; k++)
                            {
                                printf(" ");
                            }
                        }
                        else
                        {
                            for (int k = 0; k < width; k++)
                            {
                                printf("X");
                            }
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}
