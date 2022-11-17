/// DAVE MARTIN D. JORNALES
/// BSIS-NS-2B
/// DSA PROJECT

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

///GLOBAL VARIABLES
//=====================================

int code = 33;                      /// For encrypt function

//=====================================

void pincode(char pin[4])           /// For pincode, used for registeracc, can't input characters, only numbers
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

//=====================================

void encrypt(char pin[4])                    /// Encrypt the pin, ch + code
{
    int i=0;
    while(pin[i]!='\0')
    {
        pin[i]=pin[i] + code;
        i++;
    }
}

//=====================================

int money_validator()                        /// For initial deposit (it avoids bugs)
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Minimum Initial Deposit is 5000\n ");
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf(">> ");
        scanf("%s", money);
        for (int i = 0; i < strlen(money); i++)
        {
            if (!isdigit(money[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\t\t");
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(money);
        }

    }
    while(atoi(money) < 5000 || atoi(money) > 50000);
    return atoi(money);
}

//=====================================

int day_validator()                          /// For Birthday (it avoids bugs)
{
    int isAllDigit = 1;
    char day[3];
    do
    {
        isAllDigit = 1;
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Day[dd]: ");
        printf(">> ");
        scanf("%s", day);
        for (int i = 0; i < strlen(day); i++)
        {
            if (!isdigit(day[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\t\t");
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(day);
        }
    }
    while(atoi(day) >= 32 || atoi(day) < 1);
    return atoi(day);
}

//=====================================

int month_validator()                        /// For Birthday (it avoids bugs)
{
    int isAllDigit = 1;
    char month[3];
    do
    {
        isAllDigit = 1;
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Month[mm]: ");
        printf(">> ");
        scanf("%s", month);
        for (int i = 0; i < strlen(month); i++)
        {
            if (!isdigit(month[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\t\t");
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(month);
        }
    }
    while(atoi(month) >= 13 || atoi(month) < 1);
    return atoi(month);
}

//=====================================

int year_validator()                         /// For Birthday (it avoids bugs)
{
    int isAllDigit = 1;
    char year[5];
    do
    {
        isAllDigit = 1;
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Year[yyyy]: ");
        printf(">> ");
        scanf("%s", year);
        for (int i = 0; i < strlen(year); i++)
        {
            if (!isdigit(year[i]))
            {
                isAllDigit = 0;
                printf("\t\t\t\t\t\t\t\t\t\t");
                printf("Invalid Input!\n");
                break;
            }
        }

        if (isAllDigit)
        {
            atoi(year);
        }
    }
    while(atoi(year) >= 2022 || atoi(year) < 1902);
    return atoi(year);
}

//=====================================

void contactChecker(char contact[13])        /// For Contact Number (it avoids bugs)
{
    int index =0;
    char ch;
    while(index<11)
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

        if(ch == 13 && index == 8)
        {
            break;
        }

        if(isdigit(ch))
        {
            contact[index++]=ch;
            putch(ch);
        }
    }
    if (index==11)
        contact[index++]=ch;
    contact[index]='\0';
}

//=====================================

char * removeSpacesFromStr(char *string)     /// For removing space/s, it avoids bugs when retrieving data.
{
    // non_space_count to keep the frequency of non space characters
    int non_space_count = 0;

    //Traverse a string and if it is non space character then, place it at index non_space_count
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;//non_space_count incremented
        }
    }

    //Finally placing final character at the string end
    string[non_space_count] = '\0';
    return string;
}

//=====================================

int withdraw_validator()                     /// For Withdraw (it avoids bugs)
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Enter amount you wish to withdraw");
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
            if ( atoi(money) > 10000){printf("\n\t\t\t\t\t\t\t\t\t");printf("\nYou can't withdraw greater than 10000.\nTo withdraw more than 10000 do it by batch.\n");}
            if ( atoi(money) % 100 != 0){printf("\n\t\t\t\t\t\t\t\t\t");printf("\nYou can't withdraw something not divisible by 100.\n");}
            if ( atoi(money) < 100){printf("\n\t\t\t\t\t\t\t\t\t");printf("\nYou can't withdraw something less than 100.\n");}
        }

    }
    while(atoi(money) < 100 || atoi(money) % 100 != 0 || atoi(money) > 10000);
    return atoi(money);
}

//=====================================

int deposit_validator()                      /// For Deposit (it avoids bugs)
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Enter amount you wish to deposit");
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
            if ( atoi(money) < 0){printf("\n\t\t\t\t\t\t\t\t\t");printf("\nYou can't deposit something less than 1.\n");}
            if ( atoi(money) > 500000){printf("\n\t\t\t\t\t\t\t\t\t");printf("\nYou can't deposit something greater than 500000.\n");}
        }

    }
    while(atoi(money) < 0 || atoi(money) > 500000);
    return atoi(money);
}

//=====================================

int transfer_validator()                     /// For Fund Transfer (it avoids bugs)
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Enter amount you wish to transfer");
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
