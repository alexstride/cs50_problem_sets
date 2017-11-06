#include <stdio.h>
#include <cs50.h>

int getValidHeight()
{
    int h;
    do
    {
        printf("Height: ");
        h = GetInt();
        while (h>23)
        {
            printf("Retry: ");
            h = GetInt();
        }
        
    } while (h<0);
    return h;
}

int main(void)
{
    int h;
    int width;
    h = getValidHeight();
    width = h+1;
    for(int j=2; j<h+2; j++)
    {
        for(int i=width-j; i>0; i--)
            printf(" ");
        for(int i=j; i>0; i--)
            printf("#");
        printf("\n");
    }
}