#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STRING_LENGTH 200
typedef struct Points {
    double x;
    double y;
} point;

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
    
    (*coordinates)[(*size)*2] = coordinate.x;
    (*coordinates)[(*size)*2+1]=coordinate.y;

    // printf("coordinate assigned\n");

    int i = 0;
    while(*name) {
        (*names)[*size][i++] = *name++;
    }
    (*names)[*size][i] = '\0';
    (*size)++;
    return;
}
double computeDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
void freeEveryMemory(double ** coordinates, char *** names, size_t capacity) {
    free(*coordinates);
    for(int i = 0; i < capacity; i++) {
        free((*names)[i]);
    }
    free(*names);
    return;
}
bool essentiallyEqual(double a, double b) {
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * (__DBL_EPSILON__ * 1000));
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
        char comma, colon;
        int x = scanf(" %lf %c %lf %c %199s", &tmpPoint.x, &comma, &tmpPoint.y, &colon, tmpName);
        if(comma != ',' || colon != ':') {
            printf("Invalid input.\n");
            freeEveryMemory(&coordinates, &names, capacity);
            return 0;
        }
        if(x != 5 && x != EOF) {
            printf("Invalid input.\n");
            freeEveryMemory(&coordinates, &names, capacity);
            return 0;
        }
        if(x == EOF) {
            break;
        }
      
        getPlaneInput(&coordinates, tmpPoint, &names, tmpName, &size, &capacity);
    }
    if(size < 2) {
        printf("Invalid input.\n");
        freeEveryMemory(&coordinates, &names, capacity);
        return 0;
    }

    double minDistance = __DBL_MAX__;
    for(int i = 0; i < size; i=i+1) {
        for(int j = i + 1; j < size; j=j+1) {
            double distance = computeDistance(coordinates[i*2], coordinates[i*2+1], coordinates[j*2], coordinates[j*2+1]);
            if(minDistance > distance) {
                minDistance = distance;
            }
        }
    }
    printf("Minimum airplane distance: %lf\n", minDistance);
    int pairMaxSize = (size - 1) * ((size - 1) + 1) / 2;
    int * pairTable = (int *) malloc(pairMaxSize * 2 * sizeof(int));
    size_t it = 0;
 
    for(int i = 0; i < size; i=i+1) {
        for(int j = i + 1; j < size; j=j+1) {
            double distance = computeDistance(coordinates[i*2], coordinates[i*2+1], coordinates[j*2], coordinates[j*2+1]);
            if(essentiallyEqual(distance, minDistance)) {
                pairTable[it] = i;
                pairTable[it+1] = j;
                it = it + 2;
            }
        }
    }
    printf("Pairs found: %lu\n", it / 2);
    for(int i = 0; i < size; i=i+1) {
        for(int j = i + 1; j < size; j=j+1) {
            double distance = computeDistance(coordinates[i*2], coordinates[i*2+1], coordinates[j*2], coordinates[j*2+1]);
            if(essentiallyEqual(distance, minDistance)) {
                char * str1 = names[i];
                char * str2 = names[j];
                while(*str1) {
                    printf("%c", *str1 ++);
                } 
                printf(" - ");
                while(*str2) {
                    printf("%c", *str2 ++);
                }
                printf("\n");
               
            }
        }
    }
     
    freeEveryMemory(&coordinates, &names, capacity);
    free(pairTable);
    
    return 1;
}
