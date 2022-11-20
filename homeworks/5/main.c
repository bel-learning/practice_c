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
    size_t duplicate;
} pair;

size_t pStoreSize = 0;
size_t pStoreCapacity = 0;
double latestMin = __DBL_MAX__;
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
int compareX(const void* a, const void* b)
{
    point *p1 = (point *)a,  *p2 = (point *)b;
    double diff =  (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
    if(diff >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
// Needed to sort array of points according to Y coordinate
int compareY(const void* a, const void* b)
{
    point *p1 = (point *)a, *p2 = (point *)b;
    double diff =   (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
    if(diff >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}

double stripClosest(point *strip, size_t size, double d, pair ** pairStorage) {
    double min = d;
    // printf("Strip:\n");
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = i +1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            // printf("%lu %lu\n", strip[i].index, strip[j].index);
                        
            double tmp = computeDistance(strip[i], strip[j]);
            if(essentiallyEqual(tmp, min)) {
                if(pStoreSize >= pStoreCapacity) {
                pStoreCapacity *= 2;
                *pairStorage = (pair *) realloc(*pairStorage, pStoreCapacity * sizeof(**pairStorage));
                }
                (*pairStorage)[pStoreSize].i1 = strip[i].index;
                (*pairStorage)[pStoreSize].i2 = strip[j].index;
                (*pairStorage)[pStoreSize].duplicate = 0;
                (*pairStorage)[pStoreSize].value = min;
                pStoreSize++;
            }
            if(tmp < min)
            {
                min = tmp;
                if(pStoreSize >= pStoreCapacity) {
                pStoreCapacity *= 2;
                *pairStorage = (pair *) realloc(*pairStorage, pStoreCapacity * sizeof(**pairStorage));
                }
                (*pairStorage)[pStoreSize].i1 = strip[i].index;
                (*pairStorage)[pStoreSize].i2 = strip[j].index;
                (*pairStorage)[pStoreSize].duplicate = 0;
                (*pairStorage)[pStoreSize].value = min;
                pStoreSize++;
            }
            
        }
    }
    return min;
}
double bruteForce(point * p, size_t n, pair ** pairStorage)
{
    double min = __DBL_MAX__;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i+1; j < n; j++)
        {
            // printf("%lu %lu\n", p[i].index, p[j].index);
            double tmp = computeDistance(p[i], p[j]);
            if(essentiallyEqual(tmp, min)) {
                if(pStoreSize >= pStoreCapacity) {
                pStoreCapacity *= 2;
                *pairStorage = (pair *) realloc(*pairStorage, pStoreCapacity * sizeof(**pairStorage));
                }
                (*pairStorage)[pStoreSize].i1 = p[i].index;
                (*pairStorage)[pStoreSize].i2 = p[j].index;
                (*pairStorage)[pStoreSize].duplicate = 0;
                (*pairStorage)[pStoreSize].value = min;
                pStoreSize++;
            }
            if (tmp < min)
            {
                min = tmp;
                if(pStoreSize >= pStoreCapacity) {
                pStoreCapacity *= 2;
                *pairStorage = (pair *) realloc(*pairStorage, pStoreCapacity * sizeof(**pairStorage));
                }
                (*pairStorage)[pStoreSize].i1 = p[i].index;
                (*pairStorage)[pStoreSize].i2 = p[j].index;
                (*pairStorage)[pStoreSize].duplicate = 0;
                (*pairStorage)[pStoreSize].value = min;
                pStoreSize++;
                latestMin = fmin(min, latestMin);
            }
        }
    }

    return min;
}
double closestUtil(point * Px, point * Py, size_t n, pair ** pairStorage) {
    if (n <= 3)
        return bruteForce(Px, n, pairStorage);
    size_t mid = n /2;
    point mid_point = Px[mid];

    point Pyl[n];   
    point Pyr[n]; 
    size_t li = 0, ri = 0;  
    for (size_t i = 0; i < n; i++)
    {
        if ((Py[i].x < mid_point.x || (Py[i].x == mid_point.x && Py[i].y < mid_point.y)) && li<mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }
    double dl = closestUtil(Px, Pyl, mid, pairStorage);
    double dr = closestUtil(Px + mid, Pyr, n-mid, pairStorage);    
    double d = fmin(dl, dr);
    point *strip = (point *) malloc(n * sizeof(*strip));
    size_t j = 0;
    // essentiallyEqual(d, fabs(Py[i].x - mid_point.x))
    for(size_t i = 0; i < n; i++) {
        if(fabs(Py[i].x - mid_point.x) <= d || essentiallyEqual(d, fabs(Py[i].x - mid_point.x))) {
            strip[j] = Py[i], j++;
        }
    }
    double realMin = stripClosest(strip,j ,d, pairStorage);
    free(strip);
   
    return realMin;
}
double findClosest(point * P, size_t n, pair ** pairStorage, size_t * dupExists) {
    point * Px = (point *) malloc(n * sizeof(*Px));
    point * Py = (point *) malloc(n * sizeof(*Py));
    for (size_t i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(point), compareX);
    qsort(Py, n, sizeof(point), compareY);
    // int cnt = 0;
    size_t dupli = 0;
    size_t iP = 0;
    size_t eP = 0;
    for(size_t i = 0; i < n-1; i++) {
        if(Px[i].x == Px[i+1].x && Px[i].y == Px[i+1].y) {
            // printf("Same adding to list. %lu %lu\n", Px[i].index, Px[i+1].index);
            if(pStoreSize >= pStoreCapacity) {
                pStoreCapacity *= 2;
                *pairStorage = (pair *) realloc(*pairStorage, pStoreCapacity * sizeof(**pairStorage));
            }
            (*pairStorage)[pStoreSize].i1 = Px[i].index;
            (*pairStorage)[pStoreSize].i2 = Px[i+1].index;
            (*pairStorage)[pStoreSize].duplicate = 0;
            (*pairStorage)[pStoreSize].value = 0;
            if(pStoreSize > iP) {
                iP = pStoreSize;
            }
            pStoreSize++;
            dupli++;
            *dupExists = 1;
            if(i+1 == n-1) {
                eP = pStoreSize;
                for(size_t j = iP; j <= eP; j++) {
                    (*pairStorage)[j].duplicate = dupli;
                }
                eP = 0;
                iP = 0;
                dupli = 0;
            }
        }
        else {
            if(dupli == 0) {
                (*pairStorage)[pStoreSize].duplicate = 0;
            }
            else {
                eP = pStoreSize;
                for(size_t j = iP; j <= eP; j++) {
                    (*pairStorage)[j].duplicate = dupli;
                }
                eP = 0;
                iP = 0;
                dupli = 0;
            }
        }
    }
    if(*dupExists) {
        return 0.0;
    }
    // printf("Sorted\n");
    // for(size_t i = 0; i < n; i++) {
    //     printf("%lu ", Px[i].index);
    // }
    // printf("\n");
    double min = closestUtil(Px,Py, n, pairStorage);
    free(Px);
    free(Py);

    return min;
    // return 1.0;
}
int main()
{
    point *coordinates = (point *)malloc((100) * sizeof(*coordinates));
    char **names = (char **)malloc(100 * sizeof(char *));
    for (size_t i = 0; i < 100; i++)
        names[i] = (char *)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
    point tmpPoint;
    char tmpName[MAX_STRING_LENGTH+1];
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
    size_t maxSizePairs = ((size-1)*size);
    pStoreCapacity = maxSizePairs;
    pair * pairStorage = (pair *) malloc(maxSizePairs * sizeof(*pairStorage));
    size_t dupExists = 0;                     
    double minDis = findClosest(coordinates, size, &pairStorage, &dupExists);
    printf("Minimum airplane distance: %lf\n", (minDis));
    
    pair* validPairs = (pair *) malloc(pStoreCapacity * sizeof(*validPairs));
    size_t cntj = 0;  
    size_t cnt = 0;

    for(size_t i = 0; i < pStoreSize; i++) {
        // printf("%lu %lu %lf\n", pairStorage[i].i1, pairStorage[i].i2, pairStorage[i].value);
        if(essentiallyEqual(pairStorage[i].value, minDis)) {
            // 1 3 -> 4.3 -> 
            size_t found = 0;
            for(size_t j = 0; j < cntj; j++) {
                if((pairStorage[i].i1 == validPairs[j].i1 && pairStorage[i].i2 == validPairs[j].i2) ||
                    (pairStorage[i].i1 == validPairs[j].i2 && pairStorage[i].i2 == validPairs[j].i1)
                ) {
                    found = 1;
                    break;
                }
            }
            if(!found) {
                validPairs[cnt] = pairStorage[i];
                if(validPairs[cnt].duplicate > 0) {
                    printf("duplicate: %lu %lu\n",validPairs[cnt].duplicate, ((validPairs[cnt].duplicate + 1) * validPairs[cnt].duplicate) / 2);
                    dupExists = 1;
                    
                    cntj += ((validPairs[cnt].duplicate + 1) * validPairs[cnt].duplicate) / 2; 
                }
                else 
                {
                    // printf("%lu %lu %lf\n", pairStorage[i].i1, pairStorage[i].i2, pairStorage[i].value);
                    if(!dupExists)
                        cntj++;
                }
                cnt++;

            }
        }
    }
    printf("Pairs found: %lu\n", cntj);
    for(size_t i = 0; i < cnt; i++) {
        printf("Pair: %lu %lu %lu\n", validPairs[i].i1, validPairs[i].i2, validPairs[i].duplicate);

        if(validPairs[i].duplicate > 0) {
            size_t len = validPairs[i].duplicate;
            for(size_t j = 0; j < len; j++) {
                printf("%s - %s\n", names[validPairs[i].i1], names[validPairs[i].i2]);
            }
        }
        else 
            printf("%s - %s\n", names[validPairs[i].i1], names[validPairs[i].i2]);
    }
    freeEveryMemory(&coordinates, &names, capacity);
    free(pairStorage);
    free(validPairs);
    return 1;
}
