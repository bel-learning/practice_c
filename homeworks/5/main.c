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
    size_t index;
} point;

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
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
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
    qsort(strip, size, sizeof(point), compareY);

    for(int i = 0; i < size; ++i) {
        for(int j = i +1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            if(computeDistance(strip[i], strip[j]))
                min = computeDistance(strip[i], strip[j]);
        }
    }
    for(int i = 0; i < size; i++) {
        printf(" (%lf , %lf)\n", strip[i].x, strip[i].y);
    }
    return min;
}
double bruteForce(point * p, size_t n)
{
    double min = __DBL_MAX__;
    for (size_t i = 0; i < n; i++)
        for (size_t j = i+1; j < n; j++)
            if (computeDistance(p[i], p[j]) < min)
                min = computeDistance(p[i], p[j]);
    return min;
}
double closestUtil(point * points, size_t n) {
    if (n <= 3)
        return bruteForce(points, n);
    size_t mid = n /2;
    point mid_point = points[mid];
   
    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n-mid);    
    double d = min(dl, dr);

    point strip[n];
    int j =0;
    for(int i = 0; i < n; i++) {
        if(fabs(points[i].x - mid_point.x) < d) {
            strip[j] = points[i], j++;
        }
    }
    printf("d-> %lf\n", d);
    printf("strip -> %lf\n", stripClosest(strip,j, d));
    return min(d,stripClosest(strip,j,d));
}
double findClosest(point * points, size_t n) {
    qsort(points, n, sizeof(point), compareX);
    return closestUtil(points, n);
}
int main()
{
    point *coordinates = (point *)malloc((100) * sizeof(*coordinates));
    char **names = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
        names[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));

    point tmpPoint;
    char tmpName[MAX_STRING_LENGTH];
    size_t size = 0;
    size_t capacity = 100;
    printf("Plane coordinates:\n");
    // ccommennts
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
    
    freeEveryMemory(&coordinates, &names, capacity);
    // free(pairTable);

    return 1;
}
