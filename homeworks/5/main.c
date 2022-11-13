#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 200
typedef struct Points {
    double x;
    double y;
} point;

void stripString(char * s) {
    char * d = s;
    int inSpaces = 1;
    int howManyTimesWeChangedD = 0;
    while (*s) {
        if (inSpaces) {
            if (*s != ' ') {
                inSpaces = 0;
                *d ++ = *s ++;
                howManyTimesWeChangedD++;
            } else {
                 s ++;
            }
        } else {
            if (*s == ' ') {
                inSpaces = 1;
            }
            *d ++ = *s ++;
            howManyTimesWeChangedD ++;
        }
    }
    if (howManyTimesWeChangedD > 0 && inSpaces) d --;
    *d = '\0';
}


void getPlaneInput(double ** coordinates, point coordinate, char *** names, char * name, size_t *size, size_t *capacity) 
{
    // printf("%lf %lf\n", coordinate.x, coordinate.y);
    // printf("sizeof %lu \n", sizeof(point));
    if (*size >= (*capacity) - 1)
    {
        (*capacity) = (*capacity) * 2;
        *coordinates = (double *) realloc(*coordinates, (*capacity*2) * sizeof(*coordinates));
        if(*coordinates == NULL) {
            printf("couldn't assign pointers\n");
        }
        *names = (char **) realloc(*names, (*capacity) * sizeof(*names));
        // printf("capacity: %lu\n", *capacity);
        for (int i = (*capacity)/2; i < (*capacity); i++)
        {
            (*names)[i] = (char *) malloc((MAX_STRING_LENGTH+1) * sizeof(char));   
        }
    }
    // printf("coordinate assigning\n");
    // printf("on size %lu\n", *size);
    
    (*coordinates)[*size*2] = coordinate.x;
    (*coordinates)[*size*2+1]=coordinate.y;

    // printf("coordinate assigned\n");

    int i = 0;
    while(*name) {
        (*names)[*size][i++] = *name++;
    }
    (*names)[*size][i] = '\0';
    (*size)++;
    return;
}

int main()
{
    double *coordinates = (double *)malloc((2*100) * sizeof(*coordinates));
    char **names = (char **) malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++)
        names[i] = (char *) malloc((MAX_STRING_LENGTH + 1) * sizeof(char)); 
    
    point tmpPoint;
    char tmpName[MAX_STRING_LENGTH];
    size_t size = 0;
    size_t capacity = 100;
    printf("Plane coordinates:\n");
    while (1)
    {
        int x = scanf("%lf , %lf : %199s", &tmpPoint.x, &tmpPoint.y, tmpName);
        if(x == EOF) {
            break;
        }
        // stripString(tmpName);
        getPlaneInput(&coordinates, tmpPoint, &names, tmpName, &size, &capacity);
    }
    for(size_t i = 0; i < size; i++) {
        printf("%lf %lf\n ", coordinates[i*2], coordinates[i*2+1]);
        char * pls = names[i];
        
        while(*pls) {
            printf("%c", *pls ++);
        }
        printf("\n");
    }
    
    return 0;
}
