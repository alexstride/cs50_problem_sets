#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numMins;
    printf("minutes: ");
    numMins = GetInt();
    printf("bottles: %i\n", numMins*12);
}