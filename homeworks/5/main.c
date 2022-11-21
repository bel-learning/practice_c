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
typedef struct Pairs
{
    size_t i1;
    size_t i2;
    double value;
} pair;
// Few global variables in order to avoid annoying stuff.
size_t pStoreSize = 0;
size_t pStoreCapacity = 1000;
void getPlaneInput(point **coordinates, point coordinate, char ***names, char *name, size_t *size, size_t *capacity)
{
    if (*size >= (*capacity))
    {
        (*capacity) = (*capacity) * 2;
        *coordinates = (point *)realloc(*coordinates, (*capacity) * sizeof(**coordinates));

        *names = (char **)realloc(*names, (*capacity) * sizeof(*names));
        for (size_t i = (*capacity) / 2; i < (*capacity); i++)
        {
            (*names)[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(**names));
        }
    }
    (*coordinates)[*size] = coordinate;

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
    for (size_t i = 0; i < capacity; i++)
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
int comparePair(const void *a, const void *b)
{
    pair *p1 = (pair *)a, *p2 = (pair *)b;
    double diff = (p1->i1 != p2->i2) ? (p1->i1 - p2->i1) : (p1->i2 - p2->i2);
    if (diff >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int compareX(const void *a, const void *b)
{
    point *p1 = (point *)a, *p2 = (point *)b;
    double diff = (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
    if (diff >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
// Needed to sort array of points according to Y coordinate
int compareY(const void *a, const void *b)
{
    point *p1 = (point *)a, *p2 = (point *)b;
    double diff = (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
    if (diff >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
void storeInPair(pair **pairStorage, size_t ind1, size_t ind2, double value)
{
    if (pStoreSize >= pStoreCapacity)
    {
        pStoreCapacity *= 2;
        *pairStorage = (pair *)realloc(*pairStorage, pStoreCapacity * sizeof(pair));
    }
    if (ind1 > ind2)
    {
        (*pairStorage)[pStoreSize].i1 = ind2;
        (*pairStorage)[pStoreSize].i2 = ind1;
        (*pairStorage)[pStoreSize].value = value;
    }
    else
    {
        (*pairStorage)[pStoreSize].i1 = ind1;
        (*pairStorage)[pStoreSize].i2 = ind2;
        (*pairStorage)[pStoreSize].value = value;
    }
    pStoreSize++;

    return;
}
double stripClosest(point *strip, size_t size, double d, pair **pairStorage)
{
    double min = d;
    // printf("Strip:\n");
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size && (strip[j].y - strip[i].y) <= min; ++j)
        {
            // printf("%lu %lu\n", strip[i].index, strip[j].index);
            double tmp = computeDistance(strip[i], strip[j]);
            if (essentiallyEqual(tmp, min))
            {
                storeInPair(pairStorage, strip[i].index, strip[j].index, tmp);
            }
            if (tmp < min)
            {
                min = tmp;
                storeInPair(pairStorage, strip[i].index, strip[j].index, tmp);
            }
        }
    }
    return min;
}
double bruteForce(point *p, size_t n, pair **pairStorage)
{
    double min = __DBL_MAX__;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            double tmp = computeDistance(p[i], p[j]);
            if (essentiallyEqual(tmp, min))
            {
                storeInPair(pairStorage, p[i].index, p[j].index, tmp);
            }
            if (tmp < min)
            {
                min = tmp;
                storeInPair(pairStorage, p[i].index, p[j].index, tmp);
            }
        }
    }

    return min;
}
double closestUtil(point *Px, point *Py, size_t n, pair **pairStorage)
{
    if (n <= 3)
        return bruteForce(Px, n, pairStorage);
    size_t mid = n / 2;
    point mid_point = Px[mid];

    // point Pyl[n];
    point *Pyl = (point *) malloc(n * sizeof(*Pyl));
    point *Pyr = (point *) malloc(n * sizeof(*Pyr));

    size_t li = 0, ri = 0;
    // Filtering to left and right
    for (size_t i = 0; i < n; i++)
    {
        if ((Py[i].x < mid_point.x || (Py[i].x == mid_point.x && Py[i].y < mid_point.y)) && li < mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }
    double dl = closestUtil(Px, Pyl, mid, pairStorage);
    double dr = closestUtil(Px + mid, Pyr, n - mid, pairStorage);
    double d = fmin(dl, dr);
    point *strip = (point *)malloc(n * sizeof(*strip));
    size_t j = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (fabs(Py[i].x - mid_point.x) <= d || essentiallyEqual(d, fabs(Py[i].x - mid_point.x)))
        {
            strip[j] = Py[i], j++;
        }
    }
    double realMin = stripClosest(strip, j, d, pairStorage);
    free(strip);
    free(Pyl);
    free(Pyr);
    return realMin;
}
double findClosest(point *P, size_t n, pair **pairStorage)
{
    point *Px = (point *)malloc(n * sizeof(*Px));
    point *Py = (point *)malloc(n * sizeof(*Py));
    for (size_t i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(point), compareX);
    qsort(Py, n, sizeof(point), compareY);

    double min = closestUtil(Px, Py, n, pairStorage);
    free(Px);
    free(Py);

    return min;
}
int main()
{
    point *coordinates = (point *)malloc((100) * sizeof(*coordinates));
    char **names = (char **)malloc(100 * sizeof(char *));
    for (size_t i = 0; i < 100; i++)
        names[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
    point tmpPoint;
    char tmpName[MAX_STRING_LENGTH + 1];
    size_t size = 0;
    size_t capacity = 100;
    printf("Plane coordinates:\n");
    // Input starts here
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
    // Invalid input checking
    if (size < 2)
    {
        printf("Invalid input.\n");
        freeEveryMemory(&coordinates, &names, capacity);
        return 0;
    }
    // For storing pair during the algorithm
    pair *pairStorage = (pair *)malloc(pStoreCapacity * sizeof(*pairStorage));
    // Min dis found
    double minDis = findClosest(coordinates, size, &pairStorage);
    
    printf("Minimum airplane distance: %lf\n", (minDis));
    qsort(pairStorage, pStoreSize, sizeof(pair), compareX);

// Pushing 1 more DUMMY Value to the Array in order to make looping better.
// When checking i == i + 1 it opens itself to edge cases.
// Adding 1 more dummy element would keep in check of that
    storeInPair(&pairStorage, __LONG_MAX__, __LONG_MAX__, -1);

    size_t cnt = 0;

    pair *validPairs = (pair *)malloc(pStoreCapacity * sizeof(*validPairs));

    for (size_t i = 0; i < pStoreSize - 1; i++)
    {
        if (essentiallyEqual(pairStorage[i].value, minDis))
        {
            if (!((pairStorage[i].i1 == pairStorage[i + 1].i1 && pairStorage[i].i2 == pairStorage[i + 1].i2) ||
                  (pairStorage[i].i1 == pairStorage[i + 1].i2 && pairStorage[i].i2 == pairStorage[i + 1].i1)))
            {
                validPairs[cnt++] = pairStorage[i];
            }
        }
    }
    printf("Pairs found: %lu\n", cnt);
    for (size_t i = 0; i < cnt; i++)
    {
        printf("%s - %s\n", names[validPairs[i].i1], names[validPairs[i].i2]);
    }
    freeEveryMemory(&coordinates, &names, capacity);
    free(pairStorage);
    free(validPairs);
    return 1;
}
