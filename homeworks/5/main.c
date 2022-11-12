#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 200
typedef struct Points {
    double x;
    double y;
} point;

void getPlaneInput(point ** coordinates, point coordinate, char *** names, char * name, size_t *size, size_t *capacity) 
{
    printf("%lf %lf\n", coordinate.x, coordinate.y);
    if (*size >= (*capacity) - 1)
    {
        (*capacity) = (*capacity) * 2;
        *coordinates = (point *) realloc(*coordinates, (*capacity) * sizeof(*coordinates));
        if(*coordinates == NULL) {
            printf("couldn't assign pointers\n");
        }
        *names = (char **) realloc(*names, (*capacity) * sizeof(*names));
        printf("capacity: %lu\n", *capacity);
        for (int i = (*capacity)/2; i < (*capacity); i++)
        {
            (*names)[i] = (char *) malloc((MAX_STRING_LENGTH+1) * sizeof(char));   
        }
    }
    printf("coordinate assigning\n");
    printf("on size %lu\n", *size);
    (*coordinates)[*size] = coordinate;

    printf("coordinate assigned\n");

    int i = 0;
    while(*name) {
        printf("%c\n", *name++);
        *names[*size][i] = *name++;
    }
    
    (*size)++;
    return;
}

int main()
{
    point *coordinates = (point *)malloc(100 * sizeof(point));

    char **names = (char **) malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++)
        names[i] = (char *) malloc((MAX_STRING_LENGTH) * sizeof(char)); 
    
    point tmpPoint;
    char tmpName[MAX_STRING_LENGTH];
    size_t size = 100;
    size_t capacity = 100;
    printf("Plane coordinates:\n");
    while (1)
    {
        int x = scanf("%lf , %lf : %199s", &tmpPoint.x, &tmpPoint.y, tmpName);
        if(x == EOF) {
            break;
        }
        getPlaneInput(&coordinates, tmpPoint, &names, tmpName, &size, &capacity);
    }
    for(int i = 0; i < 2; i++) {
        printf("%s\n", names[i]);
    }   
 
    return 0;
}
