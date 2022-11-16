#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "PincodeEncryption.c"

#define MAX 100

//GLOBAL VARIABLES
char an[6];
char anTo[6];
char encryptedpin[4];
float balance;
float moneyTo;

typedef struct record
{
    char accNum[6];
    char fname[31];
    char lname[31];
    char birthday[12];
    char contactNum[13];
    char encryptedPin[4];
    float initDep;

} REC;

typedef struct list
{
    REC bar[MAX]; // bank acc record
    int last;
} LIST;
LIST L;

int locate(char accN[6]);
int locPosition(char accN[6]);
int pinLocate(char Pin[4]);
int isempty();
int isfull();
int money_validator();
int day_validator();
int month_validator();
int year_validator();
void contactChecker(char contact[13]);
char * removeSpacesFromStr(char *string);
void welcome_menu();
void transaction_menu();
void insertcard();
void pin();
void removecard();
void makenull();
void add(REC x);
void withdraw();
void withdrawmain();
void deposit();
void depositmain();
void balanceinquiry();
void fundtransfer();
void transferFundTo();
void changepin();
void changepinmain();
void display();
void save();
void saveATM();
void retrieve();
void registerAcc()
{
    makenull(); // initialize the list
    retrieve(); // populate the list with saved records
    REC rec;
    int a, accnum, day, month, year; // accountnumber, accnum variable for int random number
    srand(time(0));
    //system("cls");
    printf("REGISTER ACCOUNT\n");
    accnum = 10000 + (rand() % 90000);   // generate number 10000 - 99999
    sprintf(rec.accNum, "%d", accnum); // convert int to string
    printf("Account Number: %s\n", rec.accNum);
    a = locate(rec.accNum); // to avoid duplicates
    if (a == -1)
    {
        printf("First Name: ");
        scanf(" %[^\n]s", rec.fname);
        removeSpacesFromStr(rec.fname);
        printf("Last Name: ");
        scanf(" %[^\n]s", rec.lname);
        removeSpacesFromStr(rec.lname);
        printf("Birthday\n");
        printf("Day[dd]: ");
        day = day_validator();
        printf("Month[mm]: ");
        month = month_validator();
        printf("Year[yyyy]: ");
        year = year_validator();
        sprintf(rec.birthday, "%d/%d/%d", day, month, year);
        printf("Contact Number: ");
        contactChecker(rec.contactNum);
        printf("\n\t===Initial Deposit===\n");
        rec.initDep = money_validator();
        printf("Enter PIN: ");
        pincode(rec.encryptedPin);
        encrypt(rec.encryptedPin);
        add(rec);
        save();
    }
    else
    {
        printf("\nAccount already exists!\n");
        system("pause");
    }
    display();
    welcome_menu();
}

int locate(char accN[6])
{
    int i;
    for (i = 0; i <= L.last; i++)
        if (strcmp(L.bar[i].accNum, accN) == 0)
            return (i);
    return (-1);
}

int locPosition(char accN[6])
{
    int i;
    for (i = 0; i <= L.last; i++)
    {
        if (strcmp(L.bar[i].accNum, accN) > 0)
            return (i);
    }
    return (i); // L.last+1
}

int pinLocate(char Pin[4])
{

    int i;
    for (i = 0; i <= L.last; i++)
    {
        if (strcmp(L.bar[i].encryptedPin, Pin) == 0)
        {
            return (i);
        }

    }
    return (-1); // L.last+1
}

int isempty()
{
    return (L.last == -1);
}

int isfull()
{
    return (L.last == MAX - 1);
}

int money_validator()
{
    int isAllDigit = 1;
    char money[50];
    do
    {
        isAllDigit = 1;
        printf("Minimum Initial Deposit is 5000\n ");
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
        }

    }
    while(atoi(money) < 5000 || atoi(money) > 50000);
    return atoi(money);
}

int day_validator()
{
    int isAllDigit = 1;
    char day[3];
    do
    {
        isAllDigit = 1;
        printf(">> ");
        scanf("%s", day);
        for (int i = 0; i < strlen(day); i++)
        {
            if (!isdigit(day[i]))
            {
                isAllDigit = 0;
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

int month_validator()
{
    int isAllDigit = 1;
    char month[3];
    do
    {
        isAllDigit = 1;
        printf(">> ");
        scanf("%s", month);
        for (int i = 0; i < strlen(month); i++)
        {
            if (!isdigit(month[i]))
            {
                isAllDigit = 0;
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

int year_validator()
{
    int isAllDigit = 1;
    char year[5];
    do
    {
        isAllDigit = 1;
        printf(">> ");
        scanf("%s", year);
        for (int i = 0; i < strlen(year); i++)
        {
            if (!isdigit(year[i]))
            {
                isAllDigit = 0;
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

void contactChecker(char contact[13])
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

char * removeSpacesFromStr(char *string)
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

void pin()
{
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }

    char PIN[4];
    int p, index =0;
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
            PIN[index++]=ch;
            putch('*');
        }
    }

    PIN[index]='\0';
    encrypt(PIN);
    p=pinLocate(PIN);
    fclose(fp);
    if (p==-1)
    {
        printf("\nIncorrect Pin.\n");
        system("pause");
        printf("\nEnter your pin again: ");
        pin();
    }
    else
    {
        return transaction_menu();
    }
}

void makenull()
{
    L.last = -1;
}

void add(REC x)
{
    int i, p;
    if (isfull())
    {
        printf("List is full.\n");
        system("pause");
    }
    else
    {
        p = locPosition(x.accNum);
        for (i = L.last; i >= p; i--)
        {
            L.bar[i + 1] = L.bar[i];
        }
        L.bar[p] = x;

        L.last++;
    }
}

void withdraw()
{
    makenull();
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }
    fclose(fp);
    strcpy(an, L.bar[L.last].accNum);
    int p;
    p=locate(an);
    float withdraw, changedValue;
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("CURRENT BALANCE: %.2f\n", L.bar[p].initDep);
        withdraw = withdraw_validator();
        if(withdraw > L.bar[p].initDep)
        {
            printf("\nInsufficient Balance\n");
            system("pause");
            transaction_menu();
        }
        else
        {
            L.bar[p].initDep -= withdraw;
            printf("Withdraw: %.2f\n", withdraw);
            printf("Current Balance: %.2f\n", L.bar[p].initDep);
            balance = L.bar[p].initDep;
            system("pause");
            saveATM();
            withdrawmain();
        }

    }

}

void withdrawmain()
{
    makenull();
    retrieve();
    int p;
    p=locate(an);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        L.bar[p].initDep = balance;
        save();
        transaction_menu();
    }
}

void deposit()
{
    makenull();
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }
    fclose(fp);
    strcpy(an, L.bar[L.last].accNum);
    int p;
    p=locate(an);
    float deposit, changedValue;
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        deposit = deposit_validator();
        L.bar[p].initDep += deposit;
        printf("Deposit: %.2f\n", deposit);
        printf("Current Balance: %.2f\n", L.bar[p].initDep);
        balance = L.bar[p].initDep;
        system("pause");
        saveATM();
        depositmain();
    }

}

void depositmain()
{
    makenull();
    retrieve();
    int p;
    p=locate(an);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        L.bar[p].initDep = balance;
        save();
        transaction_menu();
    }
}

void balanceinquiry()
{
    makenull();
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }
    fclose(fp);
    int i;
    printf("\n\tAccount Number: %s\n", L.bar[i].accNum);
    printf("\tName: %s, %s\n", L.bar[i].lname, L.bar[i].fname);
    printf("\tBirthday: %s\n", L.bar[i].birthday);
    printf("\tContact Number: %s\n", L.bar[i].contactNum);
    printf("\n\t\tCURRENT BALANCE: %.2f\n", L.bar[i].initDep);

    system("pause");
    transaction_menu();
}

void fundtransfer()
{
    makenull();
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }
    fclose(fp);
    strcpy(an, L.bar[L.last].accNum);
    int p;
    p=locate(an);
    float transferfund, changedValue;
    char transferTo[6];
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        printf("CURRENT BALANCE: %.2f\n", L.bar[p].initDep);
        transferfund = transfer_validator();
        if(transferfund > L.bar[p].initDep)
        {
            printf("\nInsufficient Balance\n");
            system("pause");
            transaction_menu();
        }
        else
        {
            L.bar[p].initDep -= transferfund;
            moneyTo = transferfund;
            printf("Transfer Fund: %.2f\n", transferfund);
            printf("Current Balance: %.2f\n", L.bar[p].initDep);
            printf("Transfer money to: ");
            scanf(" %[^\n]s", transferTo);
            removeSpacesFromStr(transferTo);
            strcpy(anTo, transferTo);
            balance = L.bar[p].initDep;
            system("pause");
            saveATM();
            transferFundTo();
        }
    }
}

void transferFundTo()
{
    makenull();
    retrieve();
    int p;
    p=locate(an);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        L.bar[p].initDep = balance;
        save();
    }
    p=locate(anTo);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("\t\tTRANSFER SUCCESS\n");
        L.bar[p].initDep += moneyTo;
        save();
        printf("\n\tAccount Number: %s\n", L.bar[p].accNum);
        printf("\tName: %s, %s\n", L.bar[p].lname, L.bar[p].fname);
        printf("\tBirthday: %s\n", L.bar[p].birthday);
        printf("\tContact Number: %s\n", L.bar[p].contactNum);
        printf("\n\t\tCURRENT BALANCE: %.2f\n", L.bar[p].initDep);
        system("pause");
        transaction_menu();
    }
}

void changepin()
{

    makenull();
    FILE *fp;
    REC r;
    fp=fopen("E:\\test\\account.txt","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
    }
    fclose(fp);
    strcpy(an, L.bar[L.last].accNum);
    int p;
    p=locate(an);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        printf("\nChange PIN: ");
        pincode(encryptedpin);
        encrypt(encryptedpin);
        strcpy(L.bar[p].encryptedPin, encryptedpin);
        saveATM();
        printf("\nCHANGE PIN SUCCESS");
        system("pause");
        changepinmain();
    }

}

void changepinmain()
{
    makenull();
    retrieve();
    int p;
    p=locate(an);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        strcpy(L.bar[p].encryptedPin, encryptedpin);
        save();
        transaction_menu();
    }
}

void display()
{
    int i;
    system("cls");
    for (i = 0; i <= L.last; i++)
    {
        printf("%d.) %s  ,  %s   ,  %s  ,  %s  ,  %s  , %.2f  ,  %s\n", i + 1,
               L.bar[i].accNum, L.bar[i].fname, L.bar[i].lname, L.bar[i].birthday, L.bar[i].contactNum, L.bar[i].initDep, L.bar[i].encryptedPin);
    }
    system("pause");
}

void save()
{
    FILE *fp;
    FILE *fep;
    int i;
    fp = fopen("accounts.txt", "w+");
    fep = fopen("E:\\test\\account.txt", "r+");
    fseek (fep, 0, SEEK_END);
    int size = ftell(fep);
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        for (i = 0; i <= L.last; i++)
        {
            fprintf(fp, "%s %s %s %s %s %f %s\n", L.bar[i].accNum, L.bar[i].fname, L.bar[i].lname, L.bar[i].birthday,
                    L.bar[i].contactNum, L.bar[i].initDep, L.bar[i].encryptedPin);
        }
        if (0 == size)
        {
            fprintf(fep, "%s %s %s %s %s %f %s\n", L.bar[L.last].accNum, L.bar[L.last].fname, L.bar[L.last].lname, L.bar[L.last].birthday,
                    L.bar[L.last].contactNum, L.bar[L.last].initDep, L.bar[L.last].encryptedPin);
        }
    }
    fclose(fp);
    fclose(fep);
}

void saveATM()
{
    FILE *fep;
    int i;
    fep = fopen("E:\\test\\account.txt", "w+");
    if (fep == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        for (i = 0; i <= 0; i++)
        {
            fprintf(fep, "%s %s %s %s %s %f %s\n", L.bar[i].accNum, L.bar[i].fname, L.bar[i].lname, L.bar[i].birthday,
                    L.bar[i].contactNum, L.bar[i].initDep, L.bar[i].encryptedPin);
        }
    }
    fclose(fep);
}


void retrieve()
{
    FILE *fp;
    REC r;
    fp = fopen("accounts.txt", "r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            add(r);
        }
        fclose(fp);
    }
}
