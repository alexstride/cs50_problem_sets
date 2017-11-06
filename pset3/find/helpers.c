/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //find centreIndex and centreVal
    int centreIndex = n/2;
    int centreVal = values[centreIndex];
    
    //if length is 1 and centreVal is not value searched for, return false
    if(n==1 && centreVal!=value) {return false;}
    
    //if centreVal is the value searched for, return true
    else if(centreVal == value) {return true;}
    
    else if(centreVal>value)
    {
        int newArray[centreIndex];
        for(int i=0;i<centreIndex;i++)
        {
            newArray[i] = values[i];
        }
        return search(value, newArray, centreIndex);
    }
    
    else if(centreVal<value)
    {
        int newArrayHigh[n-(centreIndex+1)];
        for(int j=(centreIndex+1);j<n;j++)
        {
            newArrayHigh[j-(centreIndex+1)] = values[j];
        }
        return search(value, newArrayHigh, n-(centreIndex+1));
    }
    else {return false;}
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //initialise a minimum index
    int minIndex = 0;
    //initialise an integer holding variable
    int hold;
    
    //loop through each of the positions, looping through subsequent positions within each loop
    for(int i=0;i<n;i++)
    {
        minIndex = i;
        for(int j=i;j<n;j++)
        {
            // if the value we are looking at is the minimum, then swap it with the one at the 
            if (values[j]<values[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            hold = values[i];
            values[i] = values[minIndex];
            values[minIndex] = hold;
        }
    }
    
    return;
}

