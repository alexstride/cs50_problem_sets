/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // create a buffer 512 bytes in length
    char* memBuffer = malloc(513);
    memBuffer[512]='\0';
    
    //Create a flag to indicate whether a file is currently being written
    int flag = 0;
    
    //create a filecounter (starting at 0) and a filename buffer pointer of length 7 bytes
    int counter = 0;
    char* fileNameBuffer = malloc(7);
    
    //open image file as inptr
    FILE* inPtr = fopen("card.raw","r");
    
    //Save the options for jpg headers
    char* option1 = malloc(5);
    sprintf(option1, "%c%c%c%c", 0xff, 0xd8, 0xff, 0xe0);
    char* option2 = malloc(5);
    sprintf(option2, "%c%c%c%c", 0xff, 0xd8, 0xff, 0xe1);
    
    //declare the target pointer
    FILE* outPtr = NULL;
    
    //keep reading into buffer until end of file is found
    while(fread(memBuffer, sizeof(char), 512, inPtr)==512)
    {
        //Is block start of jpg file?
        if (strncmp(memBuffer,option1,4)==0 || strncmp(memBuffer, option2, 4)==0)
        {
            //if yes, is there currently a file being written?
            if (flag == 1)
                //if yes, close file
                {
                    fclose(outPtr);
                }
            //increment file number counter and write filename into filename buffer
            counter++;
            sprintf(fileNameBuffer, "%03i.jpg", counter);
            //open new file and write current block into it
            outPtr = fopen(fileNameBuffer, "w");
            fwrite(memBuffer, 1, 512, outPtr);
            //set flag to 1
            flag = 1;
        }
        //if no, is there currently a file being written?
        else
        {
            //if yes, write buffer to current file
            if(flag==1)
            {
                fwrite(memBuffer, 1, 512, outPtr);
            }
        }
    }
    
    //when eof found:
    //is there a file being written?
    if (flag==1)
    {
        //if yes, write the buffer into the current file
        fwrite(memBuffer, 1, 512, outPtr);
        //change flag
        flag=0;
        //close file
        fclose(outPtr);
    }
        
    //close image file
    fclose(inPtr);
    //free malloc-ed memory
    free(memBuffer);
    free(option1);
    free(option2);
    free(fileNameBuffer);
}