#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int *arr;
    int size;
} ArrayWithSize;

typedef struct
{
    int a;
    int b;
    size_t answers[20][2];
} twoValue;


void removeNL(char *s);
int initialSizes[4];
int op = 0;

twoValue search(ArrayWithSize* tokens, int size, int a, int b, int aTurn, size_t **answer, size_t ansI)
{
    op++;
    // printf("a: %d b: %d\n",a,b);
   
    if (size == 0)
    {
        twoValue ab;
        ab.a = a;
        ab.b = b;
        return ab;
    }
    if (aTurn)
    {
        twoValue cur;
        size_t cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                
                tokens[i].size--;
                tokens[i].arr++;
                cur = search(tokens, size - 1, a + current, b, 0, answer, ansI+1);
                tokens[i].size++;
                tokens[i].arr--;
                if(cnt == 0) {
                    max = cur;
                }
                if(max.a <= cur.a) {
                    max = cur;
                    max.answers[ansI][0] = i;
                    max.answers[ansI][1] = initialSizes[i]-tokens[i].size;
                }
                cnt++;
            }
        }
        
        return max;
    }
    else {
        twoValue cur;
        size_t cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        // if A have chosen the best, it's either the second best or the new element...
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                // answer[ansI][0] = i;
                // answer[ansI][1] = initialSizes[i]-tokens[i].size;
                tokens[i].size--;
                tokens[i].arr++;
                cur = search(tokens, size - 1, a , b + current, 1, answer, ansI+1);
                tokens[i].size++;
                tokens[i].arr--;
                
                if(cnt == 0) {
                    max = cur;
                }
                if(max.b <= cur.b) {
                    max = cur;
                    max.answers[ansI][0] = i;
                    max.answers[ansI][1] = initialSizes[i]-tokens[i].size;
                }
                cnt++;
               
            }
        }
       
        return max;
    }
}


int insertArray(char **str, bool *colon, bool *brace1, bool *brace2, ArrayWithSize *tokens, int direction, int *index)
{
    (*str)++;
    while (*str)
    {
        // printf(">%c<\n", *str);
        while (**str == ' ')
        {
            (*str)++;
            continue;
        }
        if (**str == ':')
        {
            (*colon) = true;
            (*str)++;
            continue;
        }
        while (**str == ' ')
        {
            (*str)++;
            continue;
        }
        if (**str == '{')
        {
            (*brace1) = true;
            (*str)++;
            continue;
        }
        while (**str == ' ')
        {
            (*str)++;
            continue;
        }
        // printf(">%c<\n", **str);
        if (!isdigit(**str) && **str != '-') {
            return 0;
        }
        if (isdigit(**str) || **str == '-')
        {
            // hopefully number won't be higher than 100 digits lmao
            char numStr[100];
            int cnt = 0;
            while (isdigit(**str) || **str == '-')
            {
                numStr[cnt++] = **str;
                (*str)++;
            }
            numStr[cnt] = '\0';
            while (isspace(**str))
            {
                (*str)++;
            }
            if (**str != ',' && **str != '}')
            {
                // throw error
                return 0;
            }
            int num = atoi(numStr);
            // printf("num*Str: %s\n", num*Str);
            // printf("num: %d\n", num);
            if((*index) > 32) {
                return 0;
            }
            tokens[direction].arr[(*index)] = num;
            (*index)++;
            while (isspace(**str))
            {
                (*str)++;
            }
            if (**str != '}')
            {
                (*str)++;
            }
        }
        if (**str == '}')
        {
            (*brace2) = true;
            break;
        }
    }
    return 1;
}

void freeArray(ArrayWithSize **tokens)
{
    for (size_t i = 0; i < 4; i++)
    {
        free((*tokens)[i].arr);
    }
    free((*tokens));
}

int main()
{

    ArrayWithSize *tokens = (ArrayWithSize *)malloc(4 * sizeof(*tokens));
    for (size_t i = 0; i < 4; i++)
    {
        tokens[i].arr = (int *)malloc(33 * sizeof(int));
    }
    ArrayWithSize **cTokens = &tokens;
    printf("Tokens:\n");

    int wi = 0;
    int ni = 0;
    int si = 0;
    int ei = 0;

    size_t tokenSize = 0;
    char *str = NULL;
    size_t size = 0;
    bool inN, inW, inE, inS = false;
    while (getline(&str, &size, stdin) != EOF)
    {
        removeNL(str);
        while (*str == ' ')
        {
            str++;
            continue;
        }
        while (*str)
        {
            if (*str == 'N' || *str == 'W' || *str == 'E' || *str == 'S')
            {
                // read input
                if (*str == 'N')
                {
                    inN = true;
                    bool colon = false, brace1 = false, brace2 = false;
                    if (insertArray(&str, &colon, &brace1, &brace2, tokens, 0, &ni) == 0)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    }
                    if (!colon || !brace1 || !brace2)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    }
                    tokens[0].size = ni;
                    tokenSize += ni;
                }
                if (*str == 'W')
                {
                    inW = true;
                    bool colon = false, brace1 = false, brace2 = false;
                    if (insertArray(&str, &colon, &brace1, &brace2, tokens, 1, &wi) == 0)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    };
                    if (!colon || !brace1 || !brace2)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    }
                    tokens[1].size = wi;
                    tokenSize += wi;
                }
                if (*str == 'E')
                {
                    // printf(">%c<\n", *str);
                    inE = true;
                    bool colon = false, brace1 = false, brace2 = false;
                    if (insertArray(&str, &colon, &brace1, &brace2, tokens, 2, &ei) == 0)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    };
                    if (!colon || !brace1 || !brace2)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    }
                    tokens[2].size = ei;
                    tokenSize += ei;
                }
                if (*str == 'S')
                {
                    inS = true;
                    bool colon = false, brace1 = false, brace2 = false;
                    if (insertArray(&str, &colon, &brace1, &brace2, tokens, 3, &si) == 0)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    };
                    if (!colon || !brace1 || !brace2)
                    {
                        printf("Invalid input.\n");
                        freeArray(cTokens);
                        return EXIT_FAILURE;
                    }
                    tokens[3].size = si;
                    tokenSize += si;
                }
                // printf("outside: >%c<\n", *str);
                str++;
            }
            else {
                printf("Invalid input.\n");
                freeArray(cTokens);
                return EXIT_FAILURE;
            }
            // else
            // {
            //     printf("Invalid input.\n");
            //     freeArray(cTokens);
            //     free(str);
            //     return EXIT_FAILURE;
            //     break;
            // }
        }

        str = NULL;
    }
    if ((!inN || !inW || !inS || !inE))
    {
        printf("Invalid input.\n");
        freeArray(cTokens);
        return EXIT_FAILURE;
    }
    
    twoValue ab;
    
    size_t **answer = (size_t **) malloc(sizeof(*answer) * 128);
    for(size_t i = 0; i < 128; i++) {
        answer[i] = (size_t *) malloc(2 * sizeof(size_t));
    }

    initialSizes[0] = tokens[0].size;
    initialSizes[1] = tokens[1].size;
    initialSizes[2] = tokens[2].size;
    initialSizes[3] = tokens[3].size;

    size_t ansI = 0;
  
    ab = search(tokens, tokenSize, 0, 0, 1, answer, ansI);
    char letterMap[] = {'N', 'W', 'E', 'S'};
    // int a = 0, b = 0;
    for (size_t i = 0; i < tokenSize; i++)
    {
        if (i % 2 == 0)
        {
            // a += tokens[ab.answers[i][0]].arr[ab.answers[i][1]];
            printf("A: %c[%lu] (%d)\n", letterMap[ab.answers[i][0]], ab.answers[i][1], tokens[ab.answers[i][0]].arr[ab.answers[i][1]]);
        }
        else
        {
            // b += tokens[ab.answers[i][0]].arr[ab.answers[i][1]];
            printf("B: %c[%lu] (%d)\n", letterMap[ab.answers[i][0]], ab.answers[i][1], tokens[ab.answers[i][0]].arr[ab.answers[i][1]]);
        }
    }
    printf("Total A/B: %d/%d\n", ab.a, ab.b);
    // printf("Path check: %d/%d\n", a,b);
    
    freeArray(cTokens);
}

// helper functions
void removeNL(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
    }
}
