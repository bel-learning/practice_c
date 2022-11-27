#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct
{
    char *str;
    size_t len;
    size_t capacity;
    size_t found;
} Item;

typedef struct
{
    Item *items;
    size_t size;
    size_t capacity;
} List;
typedef struct
{
    Item *items;
    size_t size;
    size_t capacity;
    size_t num;
} Shelf;
typedef struct
{
    char *str1;
    char *str2;
    size_t shelfNum;
} Match;

void removeNL(char *s);
void printShelf(Shelf *arrShelf, size_t len);
void printList(List *arr, size_t len);


void expandShelf(Shelf **arrShelf, size_t *shelfSize, size_t *shelfCap, size_t num)
{
    if ((*shelfSize) >= (*shelfCap))
    {
        (*shelfCap) = (*shelfCap) * 2;
        *arrShelf = (Shelf *)realloc((*arrShelf), (*shelfCap) * sizeof(Shelf));
        for (size_t i = (*shelfCap) / 2; i < *shelfCap; i++)
        {
            (*arrShelf)[i].size = 0;
            (*arrShelf)[i].capacity = 100;
            (*arrShelf)[i].num = 0;
            (*arrShelf)[i].items = (Item *)malloc((*arrShelf)[i].capacity * sizeof(Item));
            for(size_t j = 0; j < (*arrShelf)[i].capacity; j++) {
                (*arrShelf)[i].items[j].capacity = 100;
                (*arrShelf)[i].items[j].str = (char *) malloc((*arrShelf)[i].items[j].capacity);
            }
        }
    }
    (*arrShelf)[*shelfSize].num = num;
    (*shelfSize)++;
    return;
}
void addToShelf(Shelf **arrShelf, size_t shelfSize, Item item)
{
    size_t shelfNum = shelfSize - 1;
    if ((*arrShelf)[shelfNum].size >= (*arrShelf)[shelfNum].capacity)
    {
        (*arrShelf)[shelfNum].capacity *= 2;
        (*arrShelf)[shelfNum].items = (Item *)realloc(((*arrShelf)[shelfNum].items), ((*arrShelf)[shelfNum].capacity) * sizeof(Item));
        for(size_t j = 0; j < (*arrShelf)[shelfNum].capacity; j++) {
                (*arrShelf)[shelfNum].items[j].capacity = 100;
                (*arrShelf)[shelfNum].items[j].str = (char *) malloc((*arrShelf)[shelfNum].items[j].capacity);
        }
    }
    (*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].capacity = item.capacity + 1;
    (*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].len = item.len;
    (*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].found = item.found;
    (*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].str = 
    (char *)realloc((*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].str,item.capacity);

    strcpy((*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size].str, item.str);
    // free(item)
    (*arrShelf)[shelfNum].size++;
    return;

    // (*arrShelf)[shelfNum].num = shelfNum;
}
void expandList(List **arrList, size_t *size, size_t *capacity)
{
    if ((*size) >= *capacity)
    {
        (*capacity) = (*capacity) * 2;
        *arrList = (List *)realloc((*arrList), (*capacity) * sizeof(**arrList));
        for (size_t i = (*capacity) / 2; i < *capacity; i++)
        {
            (*arrList)[i].capacity = 100;
            (*arrList)[i].size = 0;
            (*arrList)[i].items = (Item *)malloc((*arrList)[i].capacity * sizeof(Item));
            for(size_t j = 0; j < (*arrList)[i].capacity; j++) {
                (*arrList)[i].items[j].capacity = 100;
                (*arrList)[i].items[j].str = (char *) malloc((*arrList)[i].items[j].capacity);
            }
        }
    }
    (*size)++;
    return;
}

void addToList(List **arrList, Item item, size_t *size)
{
    size_t index = (*size) - 1;
    if ((*arrList)[index].size >= (*arrList)[index].capacity)
    {
        (*arrList)[index].capacity *= 2;
        (*arrList)[index].items = (Item *)realloc((*arrList)[index].items, (*arrList)[index].capacity * sizeof(Item));
    }
    (*arrList)[index].items[(*arrList)[index].size].capacity = item.capacity + 1;
    (*arrList)[index].items[(*arrList)[index].size].len = item.len;
    (*arrList)[index].items[(*arrList)[index].size].found = item.found;
    (*arrList)[index].items[(*arrList)[index].size].str = (char *)realloc((*arrList)[index].items[(*arrList)[index].size].str, item.capacity);

    strcpy((*arrList)[index].items[(*arrList)[index].size].str, item.str);

    (*arrList)[index].size++;
    return;
}
void freeMemory(Shelf **arrShelf, size_t shelfSize, size_t shelfCap, List **arrList, size_t listSize, size_t listCapacity)
{
    for (size_t i = 0; i < shelfCap; i++)
    {
        // printf("Freeing str\n");
            for (size_t j = 0; j < (*arrShelf)[i].capacity; i++)
            {
                // printf("freeing: %lu %lu\n",j, (*arrShelf)[i].capacity);
                free((*arrShelf)[i].items[j].str);
            }
        // printf("Done\n");

        free((*arrShelf)[i].items);
    }
    free(*arrShelf);
    for (size_t i = 0; i < listCapacity; i++)
    {
            for (size_t j = 0; j < (*arrList)[i].capacity; i++)
            {
                free((*arrList)[i].items[j].str);
            }
        free((*arrList)[i].items);
    }
    free(*arrList);

    return;
}

int patternCheck(Item it1, Item it2)
{
    size_t lenString = it2.len;
    size_t lenPattern = it1.len;
    if (strcasecmp(it2.str, it1.str) == 0)
    {
        return 2;
    }
    if (strcasestr(it2.str, it1.str))
    {
        return 1;
    }
    if (lenPattern > lenString)
    {
        if (strcasestr(it1.str, it2.str))
        {
            return 1;
        }
    }
    return 0;
}

void solve(Shelf *arrShelf, size_t shelfSize, List *arrList, size_t listSize)
{
    for (size_t i = 0; i < listSize; i++)
    {
        // main algorithm start here
        Match *answers = (Match *)malloc(arrList[i].size * sizeof(Match));
        printf("Optimized list:\n");

        for (size_t k = 0; k < shelfSize; k++)
        {
            for (size_t p = 0; p < arrShelf[k].size; p++)
            {
                for (size_t m = 0; m < arrList[i].size; m++)
                {
                    size_t foundVersion = patternCheck(arrList[i].items[m], arrShelf[k].items[p]);
                    if (foundVersion == 2 && arrList[i].items[m].found != 2)
                    {
                        arrList[i].items[m].found = 2;
                        answers[m].str1 = arrList[i].items[m].str;
                        answers[m].str2 = arrShelf[k].items[p].str;
                        answers[m].shelfNum = arrShelf[k].num;
                    }
                    else if (foundVersion == 1 && arrList[i].items[m].found == 0)
                    {
                        arrList[i].items[m].found = 1;
                        answers[m].str1 = arrList[i].items[m].str;
                        answers[m].str2 = arrShelf[k].items[p].str;
                        answers[m].shelfNum = arrShelf[k].num;
                    }
                }
            }
        }
        size_t cnt = 0;
        for (size_t k = 0; k < shelfSize; k++)
        {
            for (size_t m = 0; m < arrList[i].size; m++)
            {
                if (answers[m].shelfNum == arrShelf[k].num)
                {
                    if (arrList[i].items[m].found != 0)
                    {
                        printf(" %lu. %s -> #%lu %s\n", cnt, answers[m].str1, answers[m].shelfNum, answers[m].str2);
                        cnt++;
                    }
                }
            }
        }
        for (size_t m = 0; m < arrList[i].size; m++)
        {
            if (arrList[i].items[m].found == 0)
            {
                printf(" %lu. %s -> N/A\n", cnt, arrList[i].items[m].str);
                cnt++;
            }
        }

        free(answers);
    }
    return;
    // printShelf(arrShelf, shelfNum);
    // printList(arrList, listSize);
}

int main()
{
    bool shelfAdding = false;
    bool listAdding = false;
    size_t shelfSize = 0;
    size_t shelfCapacity = 100;
    Shelf *arrShelf = (Shelf *)malloc(shelfCapacity * sizeof(*arrShelf));
    for (size_t i = 0; i < shelfCapacity; i++)
    {
        arrShelf[i].capacity = shelfCapacity;
        arrShelf[i].size = 0;
        arrShelf[i].num = 0;
        arrShelf[i].items = (Item *)malloc(arrShelf[i].capacity * sizeof(Item));
        for(size_t j = 0; j < arrShelf[i].capacity; j++) {
            arrShelf[i].items[j].capacity = 100;
            arrShelf[i].items[j].str = (char *) malloc(arrShelf[i].items[j].capacity);
        }
    }

    size_t listSize = 0;
    size_t listCapacity = 100;
    List *arrList = (List *)malloc(listCapacity * sizeof(*arrList));
    for (size_t i = 0; i < listCapacity; i++)
    {
        arrList[i].capacity = listCapacity;
        arrList[i].size = 0;
        arrList[i].items = (Item *)malloc(arrList[i].capacity * sizeof(Item));
        for(size_t j = 0; j < arrList[i].capacity; j++) {
            arrList[i].items[j].capacity = 100;
            arrList[i].items[j].str = (char *) malloc(arrList[i].items[j].capacity);
        }
    }

    char *str = NULL;
    size_t strSize = 0;

    while (getline(&str, &strSize, stdin) != EOF)
    {
        // printf("strlen -> %lu\n", strlen(tmp) );
        if (strlen(str) == 1 && str[0] == '\n')
        {
            expandList(&arrList, &listSize, &listCapacity);
            listAdding = true;
            shelfAdding = false;
            continue;
        }
        if (str[0] == '#')
        {
            shelfAdding = true;
            listAdding = false;
            int cnt = 1;
            char *numStr = (char *)malloc(strlen(str));
            size_t numI = 0;
            while (str[cnt])
            {
                numStr[numI] = str[cnt];
                cnt++;
                numI++;
            }
            size_t num = atoi(numStr);
            free(numStr);
            if (num == 0 && str[1] != '0')
            {
                free(str);
                freeMemory(&arrShelf, shelfSize, shelfCapacity, &arrList, listSize, listCapacity);
                printf("Invalid input.\n");
                return 0;
            }
            if (num != shelfSize)
            {
                free(str);
                freeMemory(&arrShelf, shelfSize, shelfCapacity, &arrList, listSize, listCapacity);
                printf("Invalid input.\n");
                return 0;
            }
            expandShelf(&arrShelf, &shelfSize, &shelfCapacity, num);
            continue;
        }

        if (shelfAdding)
        {
            Item tmpItem;
            removeNL(str);
            tmpItem.capacity = strlen(str) + 1;
            tmpItem.len = strlen(str);
            tmpItem.str = (char *)malloc(tmpItem.capacity * sizeof(char));
            tmpItem.found = 0;
            // check strlen also. If str overflows...
            strcpy(tmpItem.str, str);
            addToShelf(&arrShelf, shelfSize, tmpItem);
            free(tmpItem.str);
        }
        if (listAdding)
        {
            Item tmpItem;
            removeNL(str);
            tmpItem.capacity = strlen(str) + 1;
            tmpItem.len = strlen(str);
            tmpItem.str = (char *)malloc(tmpItem.capacity * sizeof(char));
            tmpItem.found = 0;
            strcpy(tmpItem.str, str);
            addToList(&arrList, tmpItem, &listSize);
            free(tmpItem.str);
        }
        free(str);
        str = NULL;
    }
    // size_t len = strlen(tmp);
    if (shelfSize == 0)
    {
        free(str);

        freeMemory(&arrShelf, shelfSize, shelfCapacity, &arrList, listSize, listCapacity);

        printf("Invalid input.\n");
        return 0;
    }
    if (listSize == 0)
    {
        free(str);
        freeMemory(&arrShelf, shelfSize, shelfCapacity, &arrList, listSize, listCapacity);

        printf("Invalid input.\n");
        return 0;
    }
    free(str);

    // printShelf(arrShelf, shelfSize);
    solve(arrShelf, shelfSize, arrList, listSize);
    freeMemory(&arrShelf, shelfSize, shelfCapacity, &arrList, listSize, listCapacity);

    return 0;
}

// helper functions
void printList(List *arr, size_t len)
{
    printf("To buy:\n");
    for (size_t i = 0; i < len; i++)
    {

        for (size_t j = 0; j < arr[i].size; j++)
        {
            printf("%s\n", arr[i].items[j].str);
        }
        printf("\n");
    }
    return;
}

void printShelf(Shelf *arrShelf, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("Shelf %lu\n", arrShelf[i].num);
        for (size_t j = 0; j < arrShelf[i].size; j++)
        {
            printf("%s\n", arrShelf[i].items[j].str);
        }
    }
    return;
}
void removeNL(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
    }
    return;
}
