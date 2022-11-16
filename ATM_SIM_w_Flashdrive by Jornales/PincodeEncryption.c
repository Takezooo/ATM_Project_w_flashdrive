#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

int code = 33;

void pincode(char pin[4])
{
    int index =0;
    char ch;
    while(index<4)
    {
        ch=getch();
        if (index<0)
            index=0;
        if(ch==8 && index != 0) //backspace ascii is 8
        {
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
            continue;
        }

        if(isdigit(ch))
        {
            pin[index++]=ch;
            putch('*');
        }
    }
    pin[index]='\0';
}

void encrypt(char pin[4])
{
    int i=0;
    while(pin[i]!='\0')
    {
        pin[i]=pin[i] + code;
        i++;
    }
}

int withdraw_validator()
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\nEnter amount you wish to withdraw");
        printf(">> ");
        scanf("%s", money);
        for (int i = 0; i < strlen(money); i++)
        {
            if (!isdigit(money[i]))
            {
                isAllDigit = 0;
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(money);
            if ( atoi(money) > 10000){printf("\nYou can't withdraw greater than 10000.\nTo withdraw more than 10000 do it by batch.\n");}
            if ( atoi(money) % 100 != 0){printf("\nYou can't withdraw something not divisible by 100.\n");}
            if ( atoi(money) < 100){printf("\nYou can't withdraw something less than 100.\n");}
        }

    }
    while(atoi(money) < 100 || atoi(money) % 100 != 0 || atoi(money) > 10000);
    return atoi(money);
}

int deposit_validator()
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\nEnter amount you wish to deposit");
        printf(">> ");
        scanf("%s", money);
        for (int i = 0; i < strlen(money); i++)
        {
            if (!isdigit(money[i]))
            {
                isAllDigit = 0;
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(money);
            if ( atoi(money) < 0){printf("\nYou can't deposit something less than 1.\n");}
            if ( atoi(money) > 500000){printf("\nYou can't deposit something greater than 500000.\n");}
        }

    }
    while(atoi(money) < 0 || atoi(money) > 500000);
    return atoi(money);
}

int transfer_validator()
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\nEnter amount you wish to transfer");
        printf(">> ");
        scanf("%s", money);
        for (int i = 0; i < strlen(money); i++)
        {
            if (!isdigit(money[i]))
            {
                isAllDigit = 0;
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(money);
            if ( atoi(money) < 1){printf("\nYou can't transfer something less than 1.\n");}
            if ( atoi(money) > 500000){printf("\nYou can't transfer something greater than 500000.\n");}
        }

    }
    while(atoi(money) < 1 || atoi(money) > 500000);
    return atoi(money);
}
