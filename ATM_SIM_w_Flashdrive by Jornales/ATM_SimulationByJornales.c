#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "RegisterFunction.c"

void welcome_menu();
void transaction_menu();
void insertcard();
void removecard();
int switch_validator();

int main(void)
{
    welcome_menu();
    return 0;
}

void welcome_menu()
{
    int choice;

    do{
        system("cls");
        printf("1. REGISTER NEW ACC\n");
        printf("2. INSERT ATM CARD\n");
        printf("3. EXIT\n");

        choice = switch_validator();
        switch(choice)
        {
            case 1:
                printf("REGISTER ACCOUNT\n");
                registerAcc();
                break;

            case 2:
                printf("INSERT CARD\n");
                insertcard();
                break;
            case 3:
                printf("EXIT\n");
                system("pause");
                exit(0);

        }
    }while(choice == 0);
}

void transaction_menu()
{

}

void insertcard()
{
    FILE *fp;
    do
    {
        printf("Please insert card...");
        fp=fopen("E:\\test\\account.txt","r");
        system("cls");
        if (NULL != fp)
        {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
                printf("\t\t=========NOT REGISTERED!=========\n");
                system("pause");
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
        fp=fopen("E:\\test\\account.txt","r");
    }
    while(fp!=NULL);
    fclose(fp);
    printf("Thank you for banking with TAKEZO's BANK ");

}

int switch_validator()
{
    int isAllDigit = 1;
    char inputCheck[2];
    do
    {
        isAllDigit = 1;

        printf("OPTION RANGES 1-4");
        printf(">> ");
        scanf("%s", inputCheck);
        for (int i = 0; i < strlen(inputCheck); i++)
        {
            if (!isdigit(inputCheck[i]))
            {
                isAllDigit = 0;
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(inputCheck);
        }

    }
    while(atoi(inputCheck) < 1 || atoi(inputCheck) > 3);
    return atoi(inputCheck);
}

