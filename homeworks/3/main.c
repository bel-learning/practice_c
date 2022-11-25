#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
typedef struct Date
{
        int year;
        int month;
        int day;
        int hour;
        int min;
} date;
int isLeapYear(int year)
{
        if (year % 4000 == 0)
        {
                return 0;
        }
        else if (year % 400 == 0)
        {
                return 1;
        }
        else if (year % 100 == 0)
        {
                return 0;
        }
        else if (year % 4 == 0)
        {
                return 1;
        }
        return 0;
}

int countLeapYear(date date)
{
        int year = date.year;
        if (date.month <= 2)
        {
                year--;
        }

        // printf("leap years count: %d\n", (year / 4) - (year / 100) + (year / 400) - (year / 4000));
        return (year / 4) - (year / 100) + (year / 400) - (year / 4000);
}
int whatWeekday(date date)
{
        int t[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        date.year -= date.month < 3;
        return ((date.year + date.year / 4 - date.year / 100 + date.year / 400 + t[date.month - 1] + date.day) % 7);
}
int isSunday(date date)
{
        int t[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        date.year -= date.month < 3;
        return ((date.year + date.year / 4 - date.year / 100 + date.year / 400 + t[date.month - 1] + date.day) % 7) == 0 ? 1 : 0;
}

int minute1Dif(int i1)
{
        int minutes1 = 0;
        if (i1 == 0)
        {
                minutes1 += 4;
        }
        if (i1 <= 15)
        {
                minutes1 += 1;
        }
        if (i1 <= 30)
        {
                minutes1 += 2;
        }
        if (i1 <= 45)
        {
                minutes1 += 3;
        }
        return minutes1;
}
int minute2Dif(int i2)
{
        int minutes2 = 0;
        if (i2 >= 0)
        {
                minutes2 += 4;
        }
        if (i2 >= 15)
        {
                minutes2 += 1;
        }
        if (i2 >= 30)
        {
                minutes2 += 2;
        }
        if (i2 >= 45)
        {
                minutes2 += 3;
        }
        return minutes2;
}
int convertMintoDays(int min)
{
        return (min / 1440);
}
int countDiffDays(date start, date end)
{

        int days1 = start.year * 365 + start.day;
        int days2 = end.year * 365 + end.day;
        
        for (int i = 0; i < start.month - 1; i++)
        {
                days1 += months[i];
        }
        for (int i = 0; i < end.month - 1; i++)
        {
                days2 += months[i];
        }

        days1 += countLeapYear(start);
        days2 += countLeapYear(end);
        printf("days1: %d days2: %d\n", days1, days2);
        int startDayMin = start.hour * 60 + start.min;
        int endDayMin = end.hour * 60 + end.min;
        if(startDayMin > endDayMin) {
            days2--;
        }

        return days2-days1;
}
int countDiffMins(date start, date end)
{
        // day minutes
        int startDayMin = start.hour * 60 + start.min;
        int endDayMin = end.hour * 60 + end.min;
        int dayDiff = countDiffDays(start,end);
        int totalDifMin = 0;
        if(startDayMin > endDayMin) {
            totalDifMin = ((60*24) + endDayMin) - startDayMin;
        }
        else {
            totalDifMin = (endDayMin) - startDayMin;
        }
        printf("total dif min: %d\n", totalDifMin);
        return totalDifMin;
}

int countSundays(date start, date end, int diffDay)
{
        // number of sundays between dates are just days/7 (if only intervals are higher than 7 days)
        // but there is one case where starting or the ending the is Sunday
        int usualCalculation = ((diffDay) / 7);
        int sundaysInInterval = 0;
        int startDayInWeek = whatWeekday(start);
        int remainder = (diffDay) % 7;
        if (startDayInWeek + (remainder) > 6)
        {
                sundaysInInterval++;
        }
        // printf("Sunday count: %d\n", usualCalculation + sundaysInInterval);
        return usualCalculation + sundaysInInterval;
}

int isValidTime(int minute, int hour, int day, int month, int year)
{
        if (year < 1600)
        {
                return 0;
        }
        if (month < 1 || month > 12)
        {
                return 0;
        }
        if (day < 1 || day > 31)
        {
                return 0;
        }
        if (minute < 0 || minute > 59)
        {
                return 0;
        }
        if (hour < 0 || hour > 23)
        {
                return 0;
        }
        int leapYear = isLeapYear(year);
        if (month == 2)
        {
                if (!leapYear && day > 28)
                {
                        return 0;
                }
                if (leapYear && day > 29)
                {
                        return 0;
                }
        }
        else if (day > months[month - 1])
        {
                return 0;
        }
        return 1;
}
int isValidInterval(date start, date end)
{
        if(countDiffDays(start,end) < 0)
        {
            printf("is invalid interval\n");
            return 0;
        }
       
        return 1;
}

long long int findBell1(date start, date end, int diffMin,  int sundays)
{
        // Count number of sundays within that interval
        long long int bell1 = 0;
        int diffDay = countDiffDays(start, end);


        if (diffMin == 0 && diffDay == 0)
        {
                bell1 = 0;
                if (isSunday(start))
                {
                        return 0;
                }
                if (start.min % 15 == 0)
                {
                        bell1 = start.min / 15;
                        if (start.min == 0)
                        {
                                bell1 = 4;
                        }
                }
                return bell1;
        }

        printf("Sundays: %d\n", sundays);

        diffDay -= sundays;

        // diffMin -= (sundays * 24 * 60);
        int startMinDiff = (60 - start.min);
        int endDiff = end.min;
        printf("Diff min %d\n", diffMin);
        printf("Diff days %d\n", diffDay);

        bell1 += diffDay * 240;
        bell1 += ((diffMin - startMinDiff - endDiff) / 60) * 10;

        bell1 += minute1Dif(start.min) + minute2Dif(end.min);
        return bell1;
}
long long int findBell2(date start, date end, int diffMin, int sundays)
{
        int bell2 = 0;
        int diffDay = countDiffDays(start, end);

        if (diffMin ==  0 && diffDay == 0)
        {
                if (start.min == 0)
                {
                        bell2 = ((start.hour % 12) == 0 ? 12 : (start.hour % 12));
                }
                else
                {
                        bell2 = 0;
                }
                if (isSunday(start))
                {
                        bell2 = 0;
                }
                return bell2;
        }

        // ignore sundays for the whole day
        diffDay -= sundays;

        bell2 += diffDay * 156;

        int startHour = start.hour;

        int hoursToIterate = ((diffMin) / 60) % 24;
        hoursToIterate--;

        if (start.min > end.min)
        {
                hoursToIterate++;
        }

        if (start.min != 0)
        {
                startHour++;
        }
        else
        {
                hoursToIterate++;
        }
        for (int i = startHour; i <= startHour + hoursToIterate; i++)
        {
                bell2 += ((i % 12) == 0 ? 12 : (i % 12));
        }
        return bell2;
}
date returnNextDay(date date) {
        int monthsWithLeap[12] = {31, 28 + isLeapYear(date.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(date.day + 1 > monthsWithLeap[date.month]) {
                if(date.month + 1 > 12) {
                        date.year++;
                        date.month = 1;
                        date.day = 1;
                        return date;
                }
                date.day = 1;
                date.month++;
                return date;
        }
        date.day++;

        return date;
}
date returnPreviousDate(date date) {
        int monthsWithLeap[12] = {31, 28 + isLeapYear(date.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(date.day - 1 < 1) {
                if(date.month < 1) {
                        date.day = 31;
                        date.month = 12;
                        date.year --;
                        return date;
                }
                date.day = monthsWithLeap[date.month];
                date.month--;
                return date;
        }
        date.day--;
        return date;
}

int bells(int y1, int m1, int d1, int h1, int i1,
          int y2, int m2, int d2, int h2, int i2,
          long long int *b1, long long int *b2)
{
        /* todo */
        date start, end;
        start.year = y1;
        start.month = m1;
        start.day = d1;
        start.hour = h1;
        start.min = i1;
        end.year = y2;
        end.month = m2;
        end.day = d2;
        end.hour = h2;
        end.min = i2;
        if (!isValidTime(i1, h1, d1, m1, y1))
        {
                return 0;
        }
        if (!isValidTime(i2, h2, d2, m2, y2))
        {
                return 0;
        }

        if (!isValidInterval(start, end))
        {
                printf("bad interval\n");
                return 0;
        }

        int diffMin = countDiffMins(start, end);
        int diffDay = countDiffDays(start, end);
        
        // printf("diff min: %d\n", diffMin);
        if (diffMin == 0 && diffDay == 0)
        {
                if(isSunday(start)) {
                        *b1 = 0;
                        *b2 = 0;
                        return 1;
                }
                
        }
        else {
                if (isSunday(start))
                {
                        // printf("start day is sunday!\n");
                        start = returnNextDay(start);
                        start.hour = 0;
                        start.min = 0;
                }
                if (isSunday(end))
                {
                        // printf("end day is sunday!\n");
                        end = returnPreviousDate(end);
                        end.hour = 23;
                        end.min = 59;
                }
        }
        diffMin = countDiffMins(start, end);
        diffDay = countDiffDays(start,end);
        int sundays = countSundays(start, end, diffDay);

        long long int bell1 = findBell1(start, end, diffMin, sundays);
        long long int bell2 = findBell2(start, end, diffMin, sundays);

        // bell2 end
        *b1 = bell1;
        *b2 = bell2;
        printf("%lld %lld\n", *b1, *b2);
        return 1;
}


#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
        long long int b1, b2;

        // bells(2022, 10, 1, 13, 15, 2022, 10, 1, 18, 45, &b1, &b2);

        assert(bells(2022, 10, 1, 13, 14,
                     2022, 10, 1, 18, 45, &b1, &b2) == 1 &&
               b1 == 56 && b2 == 20);
        assert(bells(2022, 10, 3, 13, 15,
                     2022, 10, 4, 11, 20, &b1, &b2) == 1 &&
               b1 == 221 && b2 == 143);
        assert(bells(2022, 10, 1, 13, 15,
                     2022, 10, 2, 11, 20, &b1, &b2) == 1 &&
               b1 == 106 && b2 == 65);
        assert(bells(2022, 10, 2, 13, 15,
                     2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
               b1 == 115 && b2 == 78);
        assert(bells(2022, 10, 1, 13, 15,
                     2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
               b1 == 221 && b2 == 143);
        assert(bells(2022, 1, 1, 13, 15,
                     2022, 10, 5, 11, 20, &b1, &b2) == 1 &&
               b1 == 56861 && b2 == 36959);
        assert(bells(2019, 1, 1, 13, 15,
                     2019, 10, 5, 11, 20, &b1, &b2) == 1 &&
               b1 == 57101 && b2 == 37115);
        assert(bells(2024, 1, 1, 13, 15,
                     2024, 10, 5, 11, 20, &b1, &b2) == 1 &&
               b1 == 57341 && b2 == 37271);
        assert(bells(1900, 1, 1, 13, 15,
                     1900, 10, 5, 11, 20, &b1, &b2) == 1 &&
               b1 == 57101 && b2 == 37115);
        assert(bells(2022, 10, 1, 0, 0,
                     2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
               b1 == 124 && b2 == 90);
        assert(bells(2022, 10, 1, 0, 15,
                     2022, 10, 1, 0, 25, &b1, &b2) == 1 &&
               b1 == 1 && b2 == 0);
        assert(bells(2022, 10, 1, 12, 0,
                     2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);
        assert(bells(2022, 11, 1, 12, 0,
                     2022, 10, 1, 12, 0, &b1, &b2) == 0 &&
               b1 == 4 && b2 == 12);
        assert(bells(2022, 10, 32, 12, 0,
                     2022, 11, 10, 12, 0, &b1, &b2) == 0 &&
               b1 == 4 && b2 == 12);
        assert(bells(2100, 2, 29, 12, 0,
                     2100, 2, 29, 12, 0, &b1, &b2) == 0 &&
               b1 == 4 && b2 == 12);
        assert(bells(2000, 2, 29, 12, 0,
                     2000, 2, 29, 12, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);
        assert(bells(2004, 2, 29, 12, 0,
                     2004, 2, 29, 12, 0, &b1, &b2) == 1 &&
               b1 == 0 && b2 == 0);
        assert(bells(2024, 2, 27, 0, 0,
                     2024, 2, 29, 23, 45, &b1, &b2) == 1 &&
               b1 == 720 && b2 == 468);
        //        my edge cases
        printf(">>>Same min, hour, day, edge cases<<<\n");
        //
        assert(bells(2022, 10, 1, 14, 45,
                     2022, 10, 1, 14, 45, &b1, &b2) == 1 &&
               b1 == 3 && b2 == 0);
        //
        assert(bells(2022, 10, 1, 14, 0,
                     2022, 10, 1, 14, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 2);

        //
        assert(bells(2022, 10, 1, 14, 59,
                     2022, 10, 1, 14, 59, &b1, &b2) == 1 &&
               b1 == 0 && b2 == 0);
        // printf("test finished\n");
        assert(bells(2022, 10, 1, 0, 0,
                     2022, 10, 1, 0, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);

        assert(bells(2022, 10, 1, 0, 0,
                     2022, 10, 1, 0, 15, &b1, &b2) == 1 &&
               b1 == 5 && b2 == 12);
        printf(">>>Invalid input tests<<<\n");

        assert(bells(1599, 10, 1, 0, 16,
                     2022, 10, 1, 0, 15, &b1, &b2) == 0);
        assert(bells(2001, 10, 1, 0, 16,
                     100, 10, 1, 0, 15, &b1, &b2) == 0);
        assert(bells(2001, 2, 29, 0, 16,
                     2022, 10, 1, 0, 15, &b1, &b2) == 0);
        assert(bells(2004, 2, 29, 0, 16,
                     2020, 2, 30, 0, 15, &b1, &b2) == 0);
        assert(bells(2004, 2, 29, 0, 16,
                     2004, 2, 29, 0, 15, &b1, &b2) == 0);
        assert(bells(3996, 2, 29, 0, 16,
                     3996, 2, 28, 23, 59, &b1, &b2) == 0);
        assert(bells(4000, 2, 29, 0, 16,
                     4000, 2, 29, 0, 15, &b1, &b2) == 0);
        assert(bells(4000, 2, 29, 1, 10,
                     4000, 2, 29, 1, 15, &b1, &b2) == 0);
        assert(bells(4000, 2, 28, 1, 60,
                     4000, 2, 28, 1, 60, &b1, &b2) == 0);

        printf(">>>Random tests<<<\n");

        assert(bells(2022, 10, 1, 13, 0,
                     2022, 10, 1, 14, 0, &b1, &b2) == 1 &&
               b1 == 14 && b2 == 3);
        assert(bells(2022, 10, 1, 13, 0,
                     2022, 10, 1, 14, 45, &b1, &b2) == 1 &&
               b1 == 20 && b2 == 3);
        assert(bells(2022, 10, 1, 13, 45,
                     2022, 10, 1, 14, 44, &b1, &b2) == 1 &&
               b1 == 10 && b2 == 2);
        assert(bells(2022, 10, 1, 13, 45,
                     2022, 10, 1, 14, 0, &b1, &b2) == 1 &&
               b1 == 7 && b2 == 2);
        //        45 -> 3 0 -> 4
        assert(bells(2022, 10, 1, 13, 45,
                     2022, 10, 1, 14, 45, &b1, &b2) == 1 &&
               b1 == 13 && b2 == 2);

        printf(">>>Sunday beginning tests<<<\n");
        assert(bells(2022, 10, 2, 13, 45,
                     2022, 10, 3, 13, 45, &b1, &b2) == 1 &&
               b1 == 140 && b2 == 91);
        assert(bells(2022, 10, 2, 13, 45,
                     2022, 10, 3, 0, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);
        assert(bells(2022, 10, 1, 23, 45,
                     2022, 10, 3, 0, 15, &b1, &b2) == 1 &&
               b1 == 8 && b2 == 12);
        assert(bells(2022, 10, 2, 23, 45,
                     2022, 10, 3, 0, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);
        assert(bells(2022, 10, 2, 23, 45,
                     2022, 10, 2, 23, 45, &b1, &b2) == 1 &&
               b1 == 0 && b2 == 0);
        // assert(bells(2022, 10, 1, 23, 59,
        //              2022, 10, 9, 0, 15, &b1, &b2) == 1 &&
        //        b1 == 1440 && b2 == 948);

        printf(">>>Sunday ending tests<<<\n");
        assert(bells(2022, 10, 1, 23, 45,
                     2022, 10, 2, 0, 50, &b1, &b2) == 1 &&
               b1 == 3 && b2 == 0);
        assert(bells(2022, 10, 1, 23, 46,
                     2022, 10, 2, 0, 50, &b1, &b2) == 1 &&
               b1 == 0 && b2 == 0);

        printf(">>>Sunday in the middle<<<\n");

        assert(bells(2022, 10, 1, 23, 46,
                     2022, 10, 2, 23, 59, &b1, &b2) == 1 &&
               b1 == 0 && b2 == 0);
        assert(bells(2022, 10, 1, 23, 46,
                     2022, 10, 3, 0, 0, &b1, &b2) == 1 &&
               b1 == 4 && b2 == 12);
        //    range with 2 sunday
        assert(bells(2022, 10, 1, 23, 46,
                     2022, 10, 10, 23, 46, &b1, &b2) == 1 &&
               b1 == 1680 && b2 == 1092);
        assert(bells(2022, 10, 3, 23, 46,
                     2022, 10, 10, 23, 46, &b1, &b2) == 1 &&
               b1 == 1440 && b2 == 936);
        assert(bells(2022, 10, 3, 23, 46,
                     2022, 10, 5, 23, 46, &b1, &b2) == 1 &&
               b1 == 480 && b2 == 312);
        assert(bells(2022, 11, 29, 23, 46,
                     2022, 12, 1, 23, 44, &b1, &b2) == 1 &&
               b1 == 477 && b2 == 312);
        //        random
        assert(bells(1700, 11, 29, 23, 46,
                     4000, 12, 1, 23, 44, &b1, &b2) == 1);

        assert(bells(2007, 11, 15, 12, 40, 2108, 6, 10, 3, 3, &b1, &b2) == 1 &&
               b1 == 7556273 && b2 == 4911570);
        assert(bells(2000, 1, 1, 0, 0, 2004, 1, 1, 0, 0, &b1, &b2) == 1);
        return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
