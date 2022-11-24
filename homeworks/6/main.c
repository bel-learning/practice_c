#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct Item {
    char * str;
    size_t size;
    size_t capacity;
} item;

addToShelf(size_t shelfNum, item ** shelf, size_t size, size_t capacity) {

}
addToList() {

}
int main () {
    size_t size = 0;
    size_t stringCapacity = 199;
    char * str = (char *) malloc(stringCapacity * sizeof(char));
    bool shelfAdding = false;
    bool listAdding = false;
    size_t shelfNum = 0;
    size_t shelfCounting = 0;
    while(fgets(str,199,stdin)) {
        
        if(str[0] == '#') {
            if(shelfNum != shelfCounting) {
            }
            shelfAdding = true;
            listAdding = false;
            shelfNum = str[1];
            shelfCounting++;

            continue;
        }
        if(strlen(str) == 1) {
            listAdding = true;
            shelfAdding = false;
            continue;
        }

        if(shelfAdding) {
            addToShelf();
        }
        if(listAdding) {
            addToList();
        }
        
    }
} 
