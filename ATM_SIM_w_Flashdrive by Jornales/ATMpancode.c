#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

int code = 33;

void pincode(char pin[7]){
int index =0;
char ch;
while(index<5){
    ch=getch();
    if (index<0)
        index=0;
    if(ch==8 && index != 0){//backspace ascii is 8
        putch('\b');
        putch(' ');
        putch('\b');
        index--;
     continue;
    }

    if(ch == 13 && index == 4){break;}

    if(isdigit(ch)){
     pin[index++]=ch;
     putch('*');
    }
}
if (index==5)
    pin[index++]=ch;
pin[index]='\0';

}

void encrypt(char pin[7]){
int i=0;
    while(pin[i]!='\0'){
        pin[i]=pin[i] + code;
        i++;
    }
}