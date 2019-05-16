#include <stdio.h>
#include <cs50.h>
#include <math.h>

// greedy algorithm to find the min number of coins for change

void cash(void);

int main(void)
{
    cash();
}

// has coins 25, 10, 5, 1 cent
void cash(void)
{
    float owing;
    do
    {
        owing = get_float("Owing Amount: ");
    }
    while (owing <= 0);
    
    int cents = round(owing * 100); // to solve floating point value imprecision, up to 8th decimal places
    int num_coins = 0;
    
    num_coins += cents / 25;
    cents = cents % 25;
    
    num_coins += cents / 10;
    cents = cents % 10;
    
    num_coins += cents / 5;
    cents = cents % 5;
    
    num_coins += cents;
    
    printf("%d", num_coins);
}

