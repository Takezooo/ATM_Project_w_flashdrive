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
