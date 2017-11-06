#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Check whether argc has a value of less that two and kick up a fuss if so
    if(argc<2)
    {
        printf("Invalid initial arguments\n");
        return 1;
    }
    
    //Get second argument of argv and convert it to an int. Set this to be c
    int c = atoi(argv[1]);
    
    //prompt for a string and set it as source
    string source = GetString();
    int length = strlen(source);
    
    //Loop through the string
    for (int i=0; i<length; i++)
    {   
        int val = source[i];
        //if character is 65-90: first formula
        if(val>64 && val<91)
        {
            printf("%c",((val-65+c)%26)+65);
        }
        else if(val>96 && val<123)
        {
            printf("%c",((val-97+c)%26)+97);
        }
        //else print char
        else
        {
            printf("%c",source[i]);
        }
    }
    printf("\n");
    return 0;
        
}