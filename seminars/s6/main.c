#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int isLeapYear(int year) {
    if(year % 400 == 0 && year % 4000 != 0) {
        return 1;
    }
    else if(year % 100 == 0) {
        return 0;
    }
    else if(year % 4 == 0) {
        return 1;
    }
    return 0;
}

int dateToIndex(int day, int month, int year, int *idx) {
    /* TODO: Your code here */
    int howManyDaysDoAMonthHas[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(year < 2000) {
        return 0;
    }
    if(month < 1 || month > 12) {
        return 0;
    }
    if(day < 1 || day > 31) {
        return 0;
    }
    if( day > howManyDaysDoAMonthHas[month-1]) {
        return 0;
    } 

    int sum = 0;
  
    for(int i = 0; i < month - 1; i++) {
        sum = sum + howManyDaysDoAMonthHas[i];
    }
    sum = sum + day;

    *idx = sum;
    printf("%d\n", *idx);
    return 1;

}


#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    return 0;
}
#endif /* __PROGTEST__ */

