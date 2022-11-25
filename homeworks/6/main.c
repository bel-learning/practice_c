#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char * str;
    size_t len;
    size_t capacity;
} Item;


typedef struct {
    Item * items;
    size_t size;
    size_t capacity;
    size_t num;
} Shelf;


void removeNL(char *s);
void printShelf(Shelf *arrShelf,size_t len);
void printList(Item * arr, size_t len);

int compareStr(const void * a, const void * b) {
    Item *s1 = (Item *)a, *s2 = (Item *)b;
    if(strcmp(s1->str, s2->str) > 0) {
        return 1;
    }
    else {
        return 0;
    }
}


void addToShelf(Shelf ** arrShelf, size_t shelfNum, Item item, size_t * arrShelfCapacity) {
    // capacity
    // add 2x more shelves
    if(shelfNum >= *arrShelfCapacity) {
        (*arrShelfCapacity) = (*arrShelfCapacity) * 2;
        *arrShelf = (Shelf *) realloc((*arrShelf), (*arrShelfCapacity) * sizeof(**arrShelf));
        for(size_t i = (*arrShelfCapacity) / 2; i < *arrShelfCapacity; i++) {
            (*arrShelf)[i].size = 0;
            (*arrShelf)[i].capacity = 100;
            (*arrShelf)[i].num = shelfNum;
            (*arrShelf)[i].items = (Item *) malloc((*arrShelf)[i].capacity * sizeof(Item));
        }
    }
    if((*arrShelf)[shelfNum].size >= (*arrShelf)[shelfNum].capacity) {
        (*arrShelf)[shelfNum].capacity *= 2;
        (*arrShelf) = (Shelf *) realloc((*arrShelf),((*arrShelf)[shelfNum].capacity) * sizeof(**arrShelf));
        
    }
    (*arrShelf)[shelfNum].items[(*arrShelf)[shelfNum].size] = item;
    (*arrShelf)[shelfNum].size++;
    // (*arrShelf)[shelfNum].num = shelfNum;
}

void addToList(Item ** arrBuy, Item item ,size_t * size, size_t *capacity) {
    if((*size) >= *capacity) {
        (*capacity) = (*capacity) * 2;
        *arrBuy = (Item *) realloc((*arrBuy),(*capacity) * sizeof(**arrBuy));
        for(size_t i = (*capacity) / 2; i < *capacity; i++) {
                (*arrBuy)[i].capacity = 200;
                (*arrBuy)[i].len = 0;
                (*arrBuy)[i].str = (char *) malloc((*arrBuy)[i].capacity * sizeof(char));
        }
    }
    (*arrBuy)[*size] = item;
    (*size) ++;
}

int main () {
    size_t stringCapacity = 199;
    bool shelfAdding = false;
    bool listAdding = false;
    size_t shelfNum = -1;
    size_t shelfArrSize = 0;
    size_t shelfArrCapacity = 100;
    Shelf * arrShelf = (Shelf *) malloc(shelfArrCapacity * sizeof(*arrShelf));
    for(size_t i = 0; i < 100; i++) {
        arrShelf[i].size = 0;
        arrShelf[i].capacity = 100;
        arrShelf[i].items = (Item *) malloc(arrShelf[i].capacity * sizeof(Item));
    }
    
    size_t toBuySize = 0;
    size_t toBuyCapacity = 100;
    
    Item * toBuyArray = (Item *) malloc(toBuyCapacity * sizeof(*toBuyArray));
    for(size_t i = 0; i < 100; i++) {
        toBuyArray[i].capacity = 200;
        toBuyArray[i].len = 0;
        toBuyArray[i].str = (char *) malloc(toBuyArray[i].capacity * sizeof(char));
    }

    char tmp[200];
    while(fgets(tmp,199,stdin) != NULL) {
        removeNL(tmp);
        // printf("len: %lu\n", strlen(tmp));
        // printf(">%s<",tmp);
        if(tmp[0] == '#') {
            shelfAdding = true;
            listAdding = false;
            shelfNum++;

            continue;
        }
        if(strlen(tmp) == 0) {
            if(toBuySize > 0) {
                // printList(toBuyArray, toBuySize);
                toBuySize = 0;
                continue;
                // realloc process ->>
            }
            listAdding = true;
            shelfAdding = false;
            continue;
        }

        if(shelfAdding) {
            Item tmpItem;
            tmpItem.capacity = 200;
            tmpItem.len = strlen(tmp);
            tmpItem.str = (char *) malloc(tmpItem.capacity * sizeof(char));
            // check strlen also. If str overflows...
            strcpy(tmpItem.str, tmp);
            addToShelf(&arrShelf, shelfNum, tmpItem, &shelfArrCapacity);
        }
        if(listAdding) {
            Item tmpItem;
            tmpItem.capacity = 200;
            tmpItem.len = strlen(tmp);
            tmpItem.str = (char *) malloc(tmpItem.capacity * sizeof(char));
            strcpy(tmpItem.str, tmp);
            addToList(&toBuyArray, tmpItem, &toBuySize, &toBuyCapacity);
        }
    }
    qsort()
    printShelf(arrShelf, shelfNum+1);
} 


// helper functions
void printList(Item * arr, size_t len) {
    printf("To buy:\n");
    for(size_t i = 0; i < len; i++) {
        printf("%s\n", arr[i].str);
    }
}

void printShelf(Shelf *arrShelf,size_t len) {
    for(size_t i = 0; i < len; i++) {
        printf("Shelf %lu\n", i);
        for(size_t j = 0; j < arrShelf[i].size; j++){
            printf("%s\n", arrShelf[i].items[j].str);
        }
    }
}
void removeNL(char * s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') { 
        s[len-1] = '\0';
    }
}