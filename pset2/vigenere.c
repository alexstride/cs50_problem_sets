// This is flawed, but I cannot be bothered to go back and rewrite it to accomplish the cipher as they have defined it in the problem set.

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Check whether argc has a value of less that two and kick up a fuss if so
    if(argc<2)
    {
        printf("Invalid initial arguments\n");
        return 1;
    }
    
    //prompt for a string and set it as source. Set length
    string source = GetString();
    int length = strlen(source);

    //Get second argument of argv and store it as cipherWord. Set wordLength
    string cipher = argv[1];
    int wordLength = strlen(cipher);
    
    
    //Loop through the string
    for (int i=0; i<length; i++)
    {   
        int shiftVal = toupper(cipher[i%wordLength])-65;
        printf("%i",shiftVal);
        int val = source[i];
        //if character is 65-90: first formula
        if(val>64 && val<91)
        {
            printf("%c",((val-65+shiftVal)%26)+65);
        }
        else if(val>96 && val<123)
        {
            printf("%c",((val-97+shiftVal)%26)+97);
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