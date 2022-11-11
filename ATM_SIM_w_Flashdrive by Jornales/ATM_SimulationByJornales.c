#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "RegisterFunction.c"

//char PIN[7];
void pin();
void insertcard();
void removecard();

int main(void)
{
    insertcard();
    return 0;
}
void insertcard()
{
    FILE *fp;
    do
    {
        printf("Please insert card...");
        fp=fopen("E:\\test\\account.csv","r");
        system("cls");
        if (NULL != fp)
        {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
                printf("\t\t=========NOT REGISTERED!=========\n");
                registerAcc();
            }
        }
    }
    while(fp==NULL);
    printf("Thank you. Please enter PIN : ");
    pin();
    fclose(fp);
}

void removecard()
{
    FILE *fp;
    do
    {
        system("cls");
        printf("Please remove card...");
        fp=fopen("E:\\test\\account.csv","r");
    }
    while(fp!=NULL);
    fclose(fp);
    printf("Thank you for banking with TAKEZO's BANK ");

}
