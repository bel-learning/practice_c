#include <stdio.h>
#include <math.h>

double interestFinder(double balance, double interestPercent, double multiplier)
{
    double currentMoney = balance;
    for(int i = 0; i < multiplier; i++) {
        currentMoney = (currentMoney * (1 + interestPercent * 0.01));
        currentMoney = trunc(currentMoney * 100) / 100;
    }
    return currentMoney;
}

int main()
{
    double cr, dr;
    printf("Enter credit interest rate [%%]:\n");
    if(scanf("%lf", &cr) != 1) {
        printf("Invalid input.\n");
        return 0;
    }
    printf("Enter debet interest rate [%%]:\n");
    if(scanf("%lf", &dr) != 1) {
        printf("Invalid input.\n");
        return 0;
    }
    int day, amount;
    double balance = 0;

    int current = 0;
    printf("Enter transactions:\n");
    while (1)
    {
        int x = scanf(" %d , %d ", &day, &amount);
        if (x != 2 || current > day)
        {
            printf("Invalid input.\n");
            return 0;
        }
        
        if (balance >= 0)
        {
            balance = interestFinder(balance, cr, day - current);
        }
        else
        {
            balance = interestFinder(balance, dr, day - current);
        }
        balance += amount;
        //
        current = day;
        if (amount == 0)
        {
            break;
        }
    }
    printf("Balance: %.2lf\n", balance);
    return 0;
}
