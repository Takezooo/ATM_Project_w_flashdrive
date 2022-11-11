#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "PincodeEncryption.c"

#define MAX 100
typedef struct record
{
    char accNum[6];
    char fname[31];
    char lname[31];
    char birthday[12];
    char contactNum[13];
    char encryptedPin[8];
    float initDep;

} REC;
typedef struct list
{
    REC bar[MAX]; // bank acc record
    int last;
} LIST;
LIST L;

void makenull();
void add(REC x);
// void update(REC x, char n[31]);
int locate(char accN[6]);
int pinLocate(char Pin[8]);
int locPosition(char accN[6]);
int isempty();
int isfull();
void display();
void save();
void retrieve();
int money_validator();
int day_validator();
int month_validator();
int year_validator();
void contactChecker(char contact[13]);
void pin();
void insertcard();
void removecard();
void registerAcc()
{
    makenull(); // initialize the list
    retrieve(); // populate the list with saved records
    REC rec;
    int choice; //for switch
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
        printf("Last Name: ");
        scanf(" %[^\n]s", rec.lname);
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
    //retrieve();
    display();
    return insertcard();
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
int locate(char accN[6])
{
    int i;
    for (i = 0; i <= L.last; i++)
        if (strcmp(L.bar[i].accNum, accN) == 0)
            return (i);
    return (-1);
}

int pinLocate(char Pin[8])
{
    int i;
    for (i = 0; i <= L.last; i++)
    {
        if (strcmp(L.bar[i].encryptedPin, Pin) > 0)
            return (i);
    }
    return (i); // L.last+1
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

void pin()
{
    retrieve();
    char PIN[8];
    int p, index =0;
    char ch;
    while(index<6)
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

        if(ch == 13 && index == 4)
        {
            encrypt(PIN);
            p=pinLocate(PIN);
            if (p==-1)
            {
                printf("Not found.\n");
                system("pause");
                registerAcc();
            }
            break;
        }

        if(isdigit(ch))
        {
            PIN[index++]=ch;
            putch('*');
        }
    }
    if (index==6){
        PIN[index++]=ch;
    }
    PIN[index]='\0';
    encrypt(PIN);
    p=pinLocate(PIN);
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
        registerAcc();
    }
    else
    {
        return removecard();
    }
}

void save()
{
    FILE *fp;
    FILE *ft;
    FILE *fep;
    int i;
    fp = fopen("accounts.csv", "w+");
    fep=fopen("E:\\test\\account.csv","w+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        for (i = 0; i <= L.last; i++)
        {
            fprintf(fp, "%s, %s, %s, %s, %s, %.2f, %s\n", L.bar[i].accNum, L.bar[i].fname, L.bar[i].lname, L.bar[i].birthday,
                    L.bar[i].contactNum, L.bar[i].initDep, L.bar[i].encryptedPin);
            fprintf(fep, "%s, %.2f\n", L.bar[i].encryptedPin, L.bar[i].initDep);
        }
    }
    fclose(fp);
    fclose(fep);
}
void retrieve()
{
    FILE *fp;
    FILE *fep;
    REC r;
    fp = fopen("accounts.csv", "r+");
    fep=fopen("E:\\test\\account.csv","r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while (!feof(fp) && !feof(fep))
        {
            fscanf(fp, "%s, %s, %s, %s, %s, %.2f, %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
            fscanf(fep, "%s, %.2f\n", r.encryptedPin, r.initDep);
            add(r);
        }
        fclose(fp);
        fclose(fep);
    }
}

