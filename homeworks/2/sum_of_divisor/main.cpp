#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

int table[10000999];
int primeTable1[10000099];

int highBound = 0;
int isPrime(int num) {
    if(num <= 1) {
        return 0;
    }
    if(num <= 3 || num == 5) {
        return 1;
    }
    if(num % 2 == 0 || num % 3 == 0 || num % 5 == 0) {
        return 0;
    }
    if(num > highBound * 2) {
        // use different prime calculation 
        for(int i = 5; i < sqrt(num); i = i + 6) {
            if(num % i == 0 || num % (i+2) == 0) {
                return 0;
            }
        }
        return 1;
    }
    if(primeTable1[num] == 0) {
            return 1;
    }
    else if(primeTable1[num] == 1) {
            return 0;
    }
    return 1;
   
}


int CheckPrimeSumDivisor(int num) {
    int sum = 0;
    int n = num;

    int ans1 = 1;
    int ans2 = 1;

    int power2 = 0;
    int base2 = 1;
    
    while (n % 2 == 0)
    {
        n = n/2;
        base2 = base2 * 2;
        power2++;
    }
    if(power2 != 0) {
        // ans1 *= ((pow(2, power2+1) - 1)/(2-1));  
        ans1 *= ((base2 * 2) -1)/(2-1);  
        // ans2 *= (pow(2, power2));
        ans2 *= base2;
    }
   

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        // While i divides n, print i and divide n
        int powers = 0;
        int base = 1;
        while (n % i == 0)
        {
            powers++;
            base = base * i;
            n = n/i;
        }
        if(powers == 0) {
            continue;
        }
        ans1 *= ((base*i) - 1)/(i-1);    
        ans2 *= (base);

    }
    if(n > 2) {
        ans1 *= ((pow(n, 2) - 1)/(n-1));
        ans2 *= n;
    }
   
    sum = ans1 - ans2;
    
    // because 1 is always a divisor of a number
    // check for primality
    if(isPrime(sum)) {
        return 1;
    }
    else {
        return 0;
    }
}

void solve(char ch, int low, int high) {

    if(ch == '?') {
        int sum = 0;
        for(int i = low; i <= high; i++) {
            if(table[i] != 0) {
                if(table[i] == 1) {
                    continue;
                } 
                sum++;
                printf("%d\n", i);
                continue;
            }
            // 
            if(isPrime(i)) {
                table[i] = 1;
                // if number is prime then
                // then the divisors of the 2num is even
                // 17 -> 1;
                // 17 * 2 == 34 -> 1 + 2 + 17
                continue;
            }
            if(CheckPrimeSumDivisor(i)) {
                table[i] = 2;
                printf("%d\n", i);
                sum++;
            }
            else {
                table[i] = 1;
            }
        }
        printf("Total: %d\n", sum);
    }
    else if(ch == '#') {
        int sum = 0;
        for(int i = low; i <= high; i++) {
            if(table[i] != 0) {
                if(table[i] == 1) {
                    continue;
                } 
                sum++;
                continue;
            }
       
            if(isPrime(i)) {
                table[i] = 1;
                continue;
            }
           
            if(CheckPrimeSumDivisor(i)) {
                table[i] = 2;
                sum++;
            }
            else {
                table[i] = 1;
            }
        }
    
        printf("Total: %d\n", sum);
    }
}

void computePrimes(int n) {

    for(int i = 2; i*i <=n; i++) {
        if(primeTable1[i] == 0) {
            for(int j= i*i; j <= n; j += i){
                primeTable1[j] = 1;
            }
        }
    }
}
int main() {
    char ch;
    int low, high;
 
    printf("Intervals:\n");
    int x = 3;

    while(x == 3) {
        x = scanf(" %c %d %d", &ch, &low, &high);
        if((x > 0 && x != 3) || (ch != '#' && ch != '?') || (low > high) || (low < 1)) {
            printf("Invalid input.\n");
            return 0;
        }
        if(x == 3) {
            // see the low or high is stored in the intervals
            // clock_t start = clock();
            // compute primes first
            computePrimes(high * 2);
            highBound = high;
            solve(ch, low, high);
            // clock_t end = clock();
            // printf("time took %f\n", (float)(end-start)/ CLOCKS_PER_SEC);
        }       
    }
    
    return 0;
}


// 3000000 - 4000000;
// 1500000 - 2000000 => 15000000 = [2, 4, 5, 6]->add (2) (3000000) ;
// even set of 3000000 - 4000000;
// increment the program with i = i + 2;
