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
    int answer[128][2];
} twoValue;
typedef struct {
    int arr[32];
    size_t size;
} tokenArr;
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}
int initialSizes[4];
int op = 0;
twoValue search(ArrayWithSize * tokens, size_t size, int a, int b, int aTurn, int ** answer, size_t ansI) {
    op++;
   
    twoValue ab;
    ab.a = a;
    ab.b = b;
    if (size == 0)
    {
        printf("<>\n");
        for(size_t i = 0; i < ansI; i++) {
            printf("path %lu %lu\n", answer[i][0], answer[i][1]);
            ab.answers[i][0] = answer[i][0];
            ab.answers[i][1] = answer[i][1];
        }
        return ab;
    }
    if (aTurn)
    {
        twoValue arr[4];
        twoValue dir[4];
        int cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        max.a = INT32_MIN;
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                answer[ansI][0] = i;
                answer[ansI][1] = initialSizes[i]-tokens[i].size;

                tokens[i].size--;
                tokens[i].arr++;
                arr[cnt++] = search(tokens, size - 1, a + current, b, 0, answer, ansI+1);
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
        twoValue arr[4];
        int cnt = 0;
        // copy tokens into tmp->
        twoValue max;
        max.b = INT32_MIN;
        for(size_t i = 0; i < 4; i++) {
            if(tokens[i].size != 0) {
                int current = tokens[i].arr[0];
                // answer[ansI][0] = i;
                // answer[ansI][1] = initialSizes[i]-tokens[i].size;
                tokens[i].size--;
                tokens[i].arr++;
                arr[cnt++] = search(tokens, size - 1, a , b + current, 1, answer, ansI+1);
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

    int tokenSize = 0;
    char *str = NULL;
    size_t size = 0;
    bool inN, inW, inE, inS = false;
    while (getline(&str, &size, stdin) != EOF)
    {
        char ** strAddress = &str;        
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
    int n[33], w[33], e[33], s[33];
    size_t nni = 0, wni = 0, eni = 0, sni = 0;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < tokens[i].size; j++)
        {
            if (i == 0)
                n[nni++] = tokens[i].arr[j];
            if (i == 1)
                w[wni++] = tokens[i].arr[j];
            if (i == 2)
                e[eni++] = tokens[i].arr[j];
            if (i == 3)
                s[sni++] = tokens[i].arr[j];
        }
    }
    // [0-3] [index];

    // size_t **answer = (size_t **)malloc(tokenSize * sizeof(*answer));
    // for (size_t i = 0; i < tokenSize; i++)
    // {
    //     answer[i] = (size_t *)malloc(2 * sizeof(**answer));
    // }
    size_t answer[128][2];
    nIni = tokens[0].size;
    wIni = tokens[1].size;
    eIni = tokens[2].size;
    sIni = tokens[3].size;

    size_t ansI = 0;
    // for (size_t i = 0; i < 4; i++)
    // {
    //     for (size_t j = 0; j < tokens[i].size; j++)
    //     {
    //         printf("%d ", tokens[i].arr[j]);
    //     }
    //     printf("\n");
    // }
    ab = search(tokenSize, n, nni, w, wni, e, eni, s, sni, 0, 0, 1, answer, ansI);
    // 3 dim for storing the answer
    // printf("Operations: %d\n", op);
    // printf("last: %d %d\n", ab.a, ab.b);
    char letterMap[] = {'N', 'W', 'E', 'S'};
    int a = 0, b = 0;
    for (size_t i = 0; i < tokenSize; i++)
    {
        // printf("dir: %lu ind: %lu\n", answer[i][0], answer[i][1]);
        // path check
        if (i % 2 == 0)
        {
            a += tokens[answer[i][0]].arr[answer[i][1]];
            printf("A: %c[%lu] (%d)\n", letterMap[answer[i][0]], answer[i][1], tokens[answer[i][0]].arr[answer[i][1]]);
        }
        else
        {
            b += tokens[answer[i][0]].arr[answer[i][1]];
            printf("B: %c[%lu] (%d)\n", letterMap[answer[i][0]], answer[i][1], tokens[answer[i][0]].arr[answer[i][1]]);
        }
        printf("%d %d\n", ab.answer[i][0], ab.answer[i][1]);
    }
    printf("Total A/B: %d/%d\n", ab.a, ab.b);
    printf("Path check: %d/%d\n", a,b);

    
    freeArray(&tokens);
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
