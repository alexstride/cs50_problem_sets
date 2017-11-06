#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // create a buffer 512 bytes in length
    char* memBuffer = malloc(513);
    
    //Create a flag to indicate whether a file is currently being written

    //create a filecounter (starting at 0) and a filename buffer pointer of length 7 bytes

    //open image file as inptr
    FILE* inPtr = fopen("card.raw","r");
    
    //Save the options for jpg headers
    char* option1 = malloc(5);
    sprintf(option1, "%c%c%c%c", 0xff, 0xd8, 0xff, 0xe0);
    char* option2 = malloc(5);
    sprintf(option2, "%c%c%c%c", 0xff, 0xd8, 0xff, 0xe1);
    
    //declare the target pointer

    //Some tester code
    size_t x = fread(memBuffer, sizeof(char), 512, inPtr);
    memBuffer[x]='\0';
    for(int i = 0; i<1000; i++)
    {
        printf("%02x", memBuffer[i]);
    }

    free(memBuffer);
    fclose(inPtr);
}
