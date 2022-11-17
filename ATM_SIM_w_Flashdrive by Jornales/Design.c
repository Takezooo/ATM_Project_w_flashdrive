/// DAVE MARTIN D. JORNALES
/// BSIS-NS-2B
/// DSA PROJECT

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<windows.h>
#include <stdlib.h>

void registerAcc();

void TakezoBankWordArt()
{
    FILE *fp;
    char c;
    fp = fopen("TakezoBankArt.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);
    char s[84] = { '\n','\n','\n','\n','\n','\t','\t','\t','\t','\t','\t','\t','\t','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',' ','P','R','E','S','S',' ','A','N','Y',' ','K','E','Y',' ','T','O',' ','C','O','N','T','I','N','U','E',' ','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','\0' };

    for (c = 0; s[c] != '\0'; c++) {
        printf("%c", s[c]);
        Sleep(1);
    }

    getch();

}

void MainMenuArt()
{
    FILE *fp;
    char c;
    fp = fopen("MainMenu.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);
}

void ThankYouArt()
{
    system("cls");
    FILE *fp;
    char c;
    fp = fopen("ThankYouArt.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
}

void TransactionMenuArt()
{
    FILE *fp;
    char c;
    fp = fopen("TransactionMenuArt.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);
}

void BalanceInquiryArt()
{
    FILE *fp;
    char c;
    fp = fopen("BalanceInquiryArt.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);
}

void NotRegisteredArt()
{
    FILE *fp;
    char c;
    fp = fopen("NotRegisteredArt.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    printf ("\n\n\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
    registerAcc();
    fclose(fp);
}

