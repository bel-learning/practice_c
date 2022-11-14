#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STRING_LENGTH 200
typedef struct Points
{
    double x;
    double y;
    double dis_from_origin;
    size_t index;
} point;
int myCmp(const void *a, const void *b)
{
    point *point1 = (point *)a;
    point *point2 = (point *)b;
    return (point1->dis_from_origin - point2->dis_from_origin);
}
void getPlaneInput(point **coordinates, point coordinate, char ***names, char *name, size_t *size, size_t *capacity)
{
    // printf("%lf %lf\n", coordinate.x, coordinate.y);
    // printf("sizeof %lu \n", sizeof(point));
    if (*size >= (*capacity) - 1)
    {
        (*capacity) = (*capacity) * 2;
        *coordinates = (point *)realloc(*coordinates, (*capacity) * sizeof(*coordinates));
        if (*coordinates == NULL)
        {
            printf("couldn't assign pointers\n");
        }
        *names = (char **)realloc(*names, (*capacity) * sizeof(*names));
        // printf("capacity: %lu\n", *capacity);
        for (int i = (*capacity) / 2; i < (*capacity); i++)
        {
            (*names)[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
        }
    }
    // printf("coordinate assigning\n");
    // printf("on size %lu\n", *size);

    (*coordinates)[(*size)] = coordinate;

    size_t i = 0;
    while (*name)
    {
        (*names)[*size][i++] = *name++;
    }
    (*names)[*size][i] = '\0';
    (*size)++;
    return;
}
double computeDistance(point a, point b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.x) * (b.y - a.x));
}
void freeEveryMemory(point **coordinates, char ***names, size_t capacity)
{
    free(*coordinates);
    for (int i = 0; i < capacity; i++)
    {
        free((*names)[i]);
    }
    free(*names);
    return;
}
bool essentiallyEqual(double a, double b)
{
    return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * (__DBL_EPSILON__ * 1000));
}
int compareX(const void* a, const void* b)
{
    point *p1 = (point *)a,  *p2 = (point *)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void* a, const void* b)
{
    point *p1 = (point *)a,   *p2 = (point *)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}
double min(double x, double y)
{
    return (x < y)? x : y;
}
double stripClosest(point *strip, int size, double d) {
    double min = d;
    for(int i = 0; i < size; i++) {
        for(int j = i +1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            min = computeDistance(strip[i], strip[j]);
        }
    } 
    return min;
}
double closestUtil(point * points_x, point * points_y, size_t n) {
    size_t mid = n /2;
    point mid_point = points_x[mid];

    point pyl[mid];
    point pyr[n-mid];
    int li = 0, ri = 0;
    for(int i = 0; i < n; i++) {
        if((points_y[i].x < mid_point.x) || (points_y[i].x == mid_point.x && points_y[i].y < mid_point.y) && (li < mid)) {
            pyl[li++]=points_y[i];
        }
        else {
            pyr[ri++]=points_y[i];
        }
    }
    double dl = closestUtil(points_x, pyl, mid);
    double dr = closestUtil(points_x + mid, pyr, n-mid);    
    double d = min(dl, dr);
    point strip[n];
    int j =0;
    for(int i = 0; i < n; i++) {
        if(fabs(points_y[i].x - mid_point.x) < d) {
            strip[j] = points_y[i], j++;
        }
    }
    return stripClosest(strip, j, d);
}
double findClosest(point * points, size_t n) {
    point points_x[n];
    point points_y[n];
    for(int i = 0; i < n; i++){
        points_x[i] = points[i];
        points_y[i] = points[i];
    }
    qsort(points_x, n, sizeof(point), compareX);
    qsort(points_y, n, sizeof(point), compareY);
    return closestUtil(points_x, points_y, n);
}
int main()
{
    point *coordinates = (point *)malloc((100) * sizeof(*coordinates));
    char **names = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
        names[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));

    point tmpPoint;
    point zeroPoint;
    zeroPoint.x = 0;
    zeroPoint.y = 0;
    char tmpName[MAX_STRING_LENGTH];
    size_t size = 0;
    size_t capacity = 100;
    printf("Plane coordinates:\n");
    while (1)
    {
        char comma, colon;
        int x = scanf(" %lf %c %lf %c %199s", &tmpPoint.x, &comma, &tmpPoint.y, &colon, tmpName);
        if (comma != ',' || colon != ':')
        {
            printf("Invalid input.\n");
            freeEveryMemory(&coordinates, &names, capacity);
            return 0;
        }
        if (x != 5 && x != EOF)
        {
            printf("Invalid input.\n");
            freeEveryMemory(&coordinates, &names, capacity);
            return 0;
        }
        if (x == EOF)
        {
            break;
        }
        tmpPoint.index = size;
        tmpPoint.dis_from_origin = computeDistance(tmpPoint, zeroPoint);
        getPlaneInput(&coordinates, tmpPoint, &names, tmpName, &size, &capacity);
    }
    if (size < 2)
    {
        printf("Invalid input.\n");
        freeEveryMemory(&coordinates, &names, capacity);
        return 0;
    }
    // qsort(coordinates, size, sizeof coordinates[0], myCmp);
    double minDis = findClosest(coordinates, size);
    printf("min dis: %lf\n", minDis);
    // for(int i = 0; i < size; i=i+1) {
    //     for(int j = i + 1; j < size; j=j+1) {
    //         double distance = computeDistance(coordinates[i].x, coordinates[i].y, coordinates[j].x, coordinates[j].y);
    //         if(minDistance > distance) {
    //             minDistance = distance;
    //         }
    //     }
    // }
    // printf("Minimum airplane distance: %lf\n", minDistance);
    // int pairMaxSize = (size - 1) * ((size - 1) + 1) / 2;
    // int * pairTable = (int *) malloc(pairMaxSize * 2 * sizeof(int));
    // size_t it = 0;

    // for(int i = 0; i < size; i=i+1) {
    //     for(int j = i + 1; j < size; j=j+1) {
    //         double distance = computeDistance(coordinates[i*2], coordinates[i*2+1], coordinates[j*2], coordinates[j*2+1]);
    //         if(essentiallyEqual(distance, minDistance)) {
    //             pairTable[it] = i;
    //             pairTable[it+1] = j;
    //             it = it + 2;
    //         }
    //     }
    // }
    // printf("Pairs found: %lu\n", it / 2);
    // for(int i = 0; i < size; i=i+1) {
    //     for(int j = i + 1; j < size; j=j+1) {
    //         double distance = computeDistance(coordinates[i*2], coordinates[i*2+1], coordinates[j*2], coordinates[j*2+1]);
    //         if(essentiallyEqual(distance, minDistance)) {
    //             char * str1 = names[i];
    //             char * str2 = names[j];
    //             while(*str1) {
    //                 printf("%c", *str1 ++);
    //             }
    //             printf(" - ");
    //             while(*str2) {
    //                 printf("%c", *str2 ++);
    //             }
    //             printf("\n");

    //         }
    //     }
    // }

    freeEveryMemory(&coordinates, &names, capacity);
    // free(pairTable);

    return 1;
}
