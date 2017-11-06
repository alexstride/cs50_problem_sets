#include <stdio.h>
#include <cs50.h>
#include <math.h>

int GetPositiveCents()
{
    float val;
    do
    {
        printf("How much change is owed?:\n");
        val = GetFloat();
    } while(val<0);
    
    return round(100*val);
}

int recurr(int val, int n)
{
    if(val<1)
    {
        return n;
    }
    else if(val>=25)
    {
        //printf("Quarter detected: passing val=%i n=%i\n",val-25,n+1);
        return recurr(val-25,n+1);
    }
    else if(val>=10)
    {
        return recurr(val-10,n+1);
    }
    else if(val>=5)
    {
        return recurr(val-5,n+1);
    }
    else if(val>=1)
    {
        return recurr(val-1,n+1);
    }
    else
    {
        //printf("%i",val);
        return -1;
    }
}
    

int main(void)
{
    int initVal = GetPositiveCents();
    //printf("Initial value of %i\n",initVal);
    printf("%i\n",recurr(initVal,0));
}