#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    int length = strlen(name);
    bool flag = true;
    for (int i=0;i<length;i++)
    {
        if(flag==true && name[i]!=' ')
        {
            printf("%c",toupper(name[i]));
            flag = false;
        }
        if(name[i]==' ') {flag=true;}
    }
    printf("\n");
}
