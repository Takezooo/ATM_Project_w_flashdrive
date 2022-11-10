#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
char PIN[7];
void pin();
void insertcard();

int main()
{
    insertcard();
    printf("\nYour PIN is %s ",PIN);
    getch();
}
void pin()
{
    int i;
    for (i = 0; i<6; i++)
    {
        PIN[i]=getch();
        putchar('*');
    }
    PIN[i]='\0';
}
void insertcard()
{
    FILE *fp;
    do
    {
        printf("Please insert card...");
        fp=fopen("E:\\test\\account.txt","r");
        system("cls");
    }
    while(fp==NULL);
    fclose(fp);
    printf("Thank you. Please enter PIN : ");
    pin();
}

void removecard()
{
    FILE *fp;
    do
    {
        system("cls");
        printf("Please remove card...");
        fp=fopen("E:\\test\\account.txt","r");
    }
    while(fp!=NULL);
    fclose(fp);
    printf("Thank you for banking with MYLUGI BANK ");

}

