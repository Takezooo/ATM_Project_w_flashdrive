/// DAVE MARTIN D. JORNALES
/// BSIS-NS-2B
/// DSA PROJECT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pincode_Encrypt_Validators.c"

#define MAX 100

///GLOBAL VARIABLES
//=====================================

char an[6];                     /// Account Number - For Flashdrive (For All Kinds of Transaction, even Balance Inquiry)
char anTo[6];                   /// Account Number To - For Main File (For Fund Transfer)
char encryptedpin[4];           /// Encrypted Pin - For Flashdrive and Main (For Change pin)
float balance;                  /// Balance - For Main File (For All Kinds of Transaction)
float moneyTo;                  /// Money To - For Main File (For Fund Transfer)

//=====================================

typedef struct record
{
    char accNum[6];             // Account Number
    char fname[31];             // First Name
    char lname[31];             // Last Name
    char birthday[12];          // Birthday
    char contactNum[13];        // Contact Number
    char encryptedPin[4];       // Encrypted Pin
    float initDep;              // Initial Deposit

} REC;

typedef struct list
{
    REC bar[MAX];               // Bank Acc Record
    int last;
} LIST;
LIST L;

//=====================================

int locate(char accN[6]);       /// To Locate Account Number
int locPosition(char accN[6]);  /// To Locate Account Number
int pinLocate(char Pin[4]);     /// To Locate Pin
int isempty();
int isfull();

void makenull();
void add(REC x);
void display();
void save();                    /// Save for main and if the flashdrive file is not empty the info will not be save there.
void saveATM();                 /// Save for flashdrive file (Used for transactions)
void retrieve();                /// Retrieve main file

void welcome_menu();            /// From ATM_MAIN_byJornales - to remove warning
void transaction_menu();        /// From ATM_MAIN_byJornales - to remove warning
void BalanceInquiryArt();       /// From Design - to remove warning

void pin();

void balanceinquiry();          /// Balance inquiry - Displays Info and Balance from flashdrive file
void withdraw();                /// Withdraw - Only flashdrive file changes
void withdrawmain();            /// Withdraw Main - Only main file changes, you call this function after you call withdraw
void deposit();                 /// Deposit - Only flashdrive file changes
void depositmain();             /// Deposit Main - Only main file changes, you call this function after you call deposit
void fundtransfer();            /// Fund Transfer - Only flashdrive file changes
void transferFundTo();          /// Transfer Fund To - Apply main file changes, you call this function after you call fundtransfer
void changepin();               /// Change Pin - Only flashdrive file changes
void changepinmain();           /// Change Pin Main - Only main file changes, you call this function after you call changepin

void gotoxy(int x, int y)       /// For positioning
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void registerAcc()
{
    makenull(); // initialize the list
    retrieve(); // populate the list with saved records
    REC rec;
    int a, accnum, day, month, year; // accountnumber, accnum variable for int random number
    srand(time(0));
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t");
    printf("REGISTER ACCOUNT\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t");
    printf("===============================\n\n");
    accnum = 10000 + (rand() % 90000);   // generate number 10000 - 99999
    sprintf(rec.accNum, "%d", accnum); // convert int to string
    printf("\t\t\t\t\t\t\t\t\t\t");
    printf("Account Number: %s\n", rec.accNum);
    a = locate(rec.accNum); // to avoid duplicates
    if (a == -1)
    {
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("First Name: ");
        scanf(" %[^\n]s", rec.fname);
        removeSpacesFromStr(rec.fname);
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Last Name: ");
        scanf(" %[^\n]s", rec.lname);
        removeSpacesFromStr(rec.lname);
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Birthday\n");
        day = day_validator();
        month = month_validator();
        year = year_validator();
        sprintf(rec.birthday, "%d/%d/%d", day, month, year);
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Contact Number: ");
        contactChecker(rec.contactNum);
        printf("\n\n\t\t\t\t\t\t\t\t\t\t");
        printf("========Initial Deposit========\n\n");
        rec.initDep = money_validator();
        printf("\t\t\t\t\t\t\t\t\t\t");
        printf("Enter PIN: ");
        pincode(rec.encryptedPin);
        encrypt(rec.encryptedPin);
        add(rec);
        save();
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\tAccount already exists!\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t");
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
    gotoxy(95,2);
    printf("DISPLAY");
    gotoxy(45,3);
    printf("==============================================================================================================\n");
    for (i = 0; i <= L.last; i++)
    {
        gotoxy(60,6+i);
        printf("%d.) %s  ,  %s   ,  %s  ,  %s  ,  %s  , %.2f  ,  %s\n\n", i + 1,
               L.bar[i].accNum, L.bar[i].fname, L.bar[i].lname, L.bar[i].birthday, L.bar[i].contactNum, L.bar[i].initDep, L.bar[i].encryptedPin);
    }
    gotoxy(45,10+i);
    printf("==============================================================================================================\n");
    gotoxy(87,11+i);
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
        printf("\n\n\t\t\t\t\t\t\t\t\t\t   Incorrect Pin.\n");
        printf("\t\t\t\t\t\t\t\t\t\t   ");
        system("pause");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("   Enter your pin again: ");
        pin();
    }
    else
    {
        return transaction_menu();
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
    BalanceInquiryArt();
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tAccount Number: %s\n", L.bar[i].accNum);
    printf("\t\t\t\t\t\t\t\t\t\tName: %s, %s\n", L.bar[i].lname, L.bar[i].fname);
    printf("\t\t\t\t\t\t\t\t\t\tBirthday: %s\n", L.bar[i].birthday);
    printf("\t\t\t\t\t\t\t\t\t\tContact Number: %s\n", L.bar[i].contactNum);
    printf("\t\t\t\t\t\t\t\t\t   ==========================================\n");
    printf("\t\t\t\t\t\t\t\t\t\tCURRENT BALANCE: %.2f\n", L.bar[i].initDep);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t");
    system("pause");
    transaction_menu();
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
    float withdraw;
    if (p==-1)
    {
        printf("Not found.\n");
        system("pause");
    }
    else
    {
        system("cls");
        gotoxy(87,2);
        printf("CURRENT BALANCE: %.2f\n", L.bar[p].initDep);
        gotoxy(45,3);
        printf("==============================================================================================================\n");
        withdraw = withdraw_validator();
        if(withdraw > L.bar[p].initDep)
        {
            printf("\n\t\t\t\t\t\t\t\t\t");
            printf("Insufficient Balance\n");
            printf("\n\t\t\t\t\t\t\t\t\t");
            system("pause");
            transaction_menu();
        }
        else
        {
            L.bar[p].initDep -= withdraw;
            printf("\n\t\t\t\t\t\t\t\t\t");
            printf("Withdraw: %.2f\n", withdraw);
            printf("\n\t\t\t\t\t\t\t\t\t");
            printf("Current Balance: %.2f\n", L.bar[p].initDep);
            balance = L.bar[p].initDep;
            printf("\n\t\t\t\t\t\t\t\t\t");
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
    float deposit;
    if (p==-1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Not found.\n");
        printf("\n\t\t\t\t\t\t\t\t\t");
        system("pause");
    }
    else
    {
        deposit = deposit_validator();
        L.bar[p].initDep += deposit;
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Deposit: %.2f\n", deposit);
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Current Balance: %.2f\n", L.bar[p].initDep);
        balance = L.bar[p].initDep;
        printf("\n\t\t\t\t\t\t\t\t\t");
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
    float transferfund;
    char transferTo[6];
    if (p==-1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Not found.\n");
        printf("\n\t\t\t\t\t\t\t\t\t");
        system("pause");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Transfer money to: ");
        scanf(" %[^\n]s", transferTo);
        removeSpacesFromStr(transferTo);
        makenull();
        retrieve();
        strcpy(anTo, transferTo);
        if(strcmp(anTo, an) == 0)
        {
            printf("\n\t\t\t\t\t\t\t\t\t");
            printf("You can't transfer fund to yourself.\n");
            printf("\n\t\t\t\t\t\t\t\t\t");
            system("pause");
            transaction_menu();
        }
        else
        {
            p=locate(anTo);
            if (p==-1)
            {
                printf("\n\t\t\t\t\t\t\t\t\t");
                printf("Account Number Not Found.\n");
                printf("\n\t\t\t\t\t\t\t\t\t");
                system("pause");
                transaction_menu();
            }
            else
            {
                makenull();
                FILE *fep;
                fep=fopen("E:\\test\\account.txt","r+");
                if (fep == NULL)
                {
                    printf("File error.\n");
                    system("pause");
                }
                else
                {
                    while (!feof(fep))
                    {
                        fscanf(fep, "%s %s %s %s %s %f %s\n", r.accNum, r.fname, r.lname, r.birthday, r.contactNum, &r.initDep, r.encryptedPin);
                        add(r);
                    }
                }
                fclose(fep);
                strcpy(an, L.bar[L.last].accNum);
                int p;
                p=locate(an);
                if (p==-1)
                {
                    printf("\n\t\t\t\t\t\t\t\t\t");
                    printf("Not found.\n");
                    printf("\n\t\t\t\t\t\t\t\t\t");
                    system("pause");
                }
                else
                {
                    printf("\n\t\t\t\t\t\t\t\t\t");
                    printf("CURRENT BALANCE: %.2f\n", L.bar[p].initDep);
                    transferfund = transfer_validator();
                    if(transferfund > L.bar[p].initDep)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t");
                        printf("Insufficient Balance\n");
                        printf("\n\t\t\t\t\t\t\t\t\t");
                        system("pause");
                        transaction_menu();
                    }
                    else
                    {
                        L.bar[p].initDep -= transferfund;
                        moneyTo = transferfund;
                        printf("\n\t\t\t\t\t\t\t\t\t");
                        printf("Transfer Fund: %.2f\n", transferfund);
                        printf("\n\t\t\t\t\t\t\t\t\t");
                        printf("Current Balance: %.2f\n", L.bar[p].initDep);
                        balance = L.bar[p].initDep;
                        printf("\n\t\t\t\t\t\t\t\t\t");
                        system("pause");
                        saveATM();
                        transferFundTo();
                    }
                }
            }
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
        printf("\n\n\n\t\t\t\t\t\t\t\t\t\tAccount Number: %s\n", L.bar[p].accNum);
        printf("\t\t\t\t\t\t\t\t\t\tName: %s, %s\n", L.bar[p].lname, L.bar[p].fname);
        printf("\t\t\t\t\t\t\t\t\t\tBirthday: %s\n", L.bar[p].birthday);
        printf("\t\t\t\t\t\t\t\t\t\tContact Number: %s\n", L.bar[p].contactNum);
        printf("\t\t\t\t\t\t\t\t\t   ==========================================\n");
        printf("\t\t\t\t\t\t\t\t\t\tCURRENT BALANCE: %.2f\n", L.bar[p].initDep);
        printf("\n\n\t\t\t\t\t\t\t\t\t\t");
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
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Not found.\n");
        printf("\n\t\t\t\t\t\t\t\t\t");
        system("pause");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("Change PIN: ");
        pincode(encryptedpin);
        encrypt(encryptedpin);
        strcpy(L.bar[p].encryptedPin, encryptedpin);
        saveATM();
        printf("\n\t\t\t\t\t\t\t\t\t");
        printf("CHANGE PIN SUCCESS\n");
        printf("\n\t\t\t\t\t\t\t\t\t");
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
