/// DAVE MARTIN D. JORNALES
/// BSIS-NS-2B
/// DSA PROJECT

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Register_Transactions.c"
#include "Design.c"

void welcome_menu();
void transaction_menu();
void insertcard();
void removecard();
int switch_validator_welcome();
int switch_validator_transaction();

int main(void)
{
    HWND console = GetConsoleWindow();
    MoveWindow(console, 20, 90, 1450, 720, TRUE);
    system("color 0e");
    TakezoBankWordArt();
    welcome_menu();
    return 0;
}

void welcome_menu()
{
    int choice;

    do{
        system("cls");
        MainMenuArt();
        choice = switch_validator_welcome();
        switch(choice)
        {
            case 1:
                system("cls");
                registerAcc();
                break;

            case 2:
                insertcard();
                break;
            case 3:
                ThankYouArt();
                system("pause");
                exit(0);

        }
    }while(choice == 0);
}

void transaction_menu()
{
      int choice;

    do{
        system("cls");
        TransactionMenuArt();
        choice = switch_validator_transaction();
        switch(choice)
        {
            case 1:
                system("cls");
                balanceinquiry();
                break;

            case 2:
                system("cls");
                printf("\n\t\t\t\t\t\t\t\t\t");
                printf("WITHDRAW\n");
                withdraw();
                break;

            case 3:
                system("cls");
                printf("\n\t\t\t\t\t\t\t\t\t");
                printf("DEPOSIT\n");
                deposit();
                break;

            case 4:
                system("cls");
                printf("\n\t\t\t\t\t\t\t\t\t");
                printf("FUND TRANSFER\n");
                fundtransfer();
                break;

            case 5:
                system("cls");
                printf("\n\t\t\t\t\t\t\t\t\t");
                printf("CHANGE PIN\n");
                changepin();
                break;

            case 6:
                system("cls");
                printf("\n\n\t\t\t\t\t\t\t\t\t\t\t");
                system("pause");
                removecard();

        }
    }while(choice == 0);
}

void insertcard()
{
    FILE *fp;
    int i = 80;
    do
    {
            gotoxy(87,6);    printf("Please insert Flash Drive...");

            gotoxy(i,10);    printf("            __________________________ ");
            gotoxy(i,11);    printf(" __________/                          |");
            gotoxy(i,12);   printf("|     _    |                          |");
            gotoxy(i,13);   printf("|    [ ]   |                          |");
            gotoxy(i,14);   printf("|    [_]   |                          |");
            gotoxy(i,15);   printf("|     _    |                          |");
            gotoxy(i,16);   printf("|    [ ]   |                          |");
            gotoxy(i,17);   printf("|    [_]   |                          |");
            gotoxy(i,18);   printf("|__________|                          |");
            gotoxy(i,19);   printf("           \\__________________________|");

            gotoxy(100,9);   printf(" _ ");
            gotoxy(100,10);   printf("| |");
            gotoxy(100,11);   printf("| |");
            gotoxy(100,12);  printf("| |");
            gotoxy(100,13);  printf("|_|");
            gotoxy(100,14);  printf("| |");
            gotoxy(100,15);  printf("|_|");
            gotoxy(100,16);  printf("| |");
            gotoxy(100,17);  printf("| |");
            gotoxy(100,18);  printf("| |");
            gotoxy(100,19);  printf("| |");
            gotoxy(100,20);  printf("|_|");

            gotoxy(79,9);    printf(" ------");
            gotoxy(79,10);   printf("|      |");
            gotoxy(79,11);   printf("|      |");
            gotoxy(79,12);   printf("|      |");
            gotoxy(79,13);   printf("|      |");
            gotoxy(79,14);   printf("|      |");
            gotoxy(79,15);   printf("|      |");
            gotoxy(79,16);   printf("|      |");
            gotoxy(79,17);   printf("|      |");
            gotoxy(79,18);   printf("|      |");
            gotoxy(79,19);   printf("|      |");
            gotoxy(79,20);   printf(" ------");

            if(i == 80)
                i += 6;
            else
                i -= 6;
        fp=fopen("E:\\test\\account.txt","r");
        Sleep(250);
        system("cls");
        if (NULL != fp)
        {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
                NotRegisteredArt();
            }
        }
    }
    while(fp==NULL);
    gotoxy(83,8);  printf("==================================");
    gotoxy(83,10); printf("Thank you. Please enter PIN : ");
    pin();
    fclose(fp);
}

void removecard()
{
    FILE *fp;
    do
    {
        system("cls");
        gotoxy(83,8);  printf("==================================");
        gotoxy(89,10); printf("Please remove card...");
        gotoxy(83,12);  printf("==================================");
        fp=fopen("E:\\test\\account.txt","r");
    }
    while(fp!=NULL);
    fclose(fp);
    ThankYouArt();
    printf("\n\n\t\t\t\t\t\t\t\t\t\t   ");
    system("pause");
    welcome_menu();
}

int switch_validator_welcome()
{
    int isAllDigit = 1;
    char inputCheck[2];
    do
    {
        isAllDigit = 1;
        printf("\n\n\n\n\t\t\t\t\t\t\t\t\tOPTION RANGES 1-3");
        printf("  >>  ");
        scanf("%s", inputCheck);
        for (int i = 0; i < strlen(inputCheck); i++)
        {
            if (!isdigit(inputCheck[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\tInvalid Input!\n");
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

int switch_validator_transaction()
{
    int isAllDigit = 1;
    char inputCheck[2];
    do
    {
        isAllDigit = 1;
        printf("\t\t\t\t\t\t\t\t\t\tOPTION RANGES 1-6");
        printf("  >>  ");
        scanf("%s", inputCheck);
        for (int i = 0; i < strlen(inputCheck); i++)
        {
            if (!isdigit(inputCheck[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\tInvalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(inputCheck);
        }

    }
    while(atoi(inputCheck) < 1 || atoi(inputCheck) > 6);
    return atoi(inputCheck);
}
