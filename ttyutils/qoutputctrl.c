#include<stdio.h>
#include"qoutputctrl.h"


void qsetoutxy(int x,int y){
    printf("%c[%d;%df", 0x1b, y, x);
}

void qmoveup(int a){
    printf("%c[%dA",0x1b,a);
}

void qmovedown(int a){
    printf("%c[%dB",0x1b,a);
}

void qmoveleft(int a){
    printf("%c[%dD",0x1b,a);  
}

void qmoveright(int a){
    printf("%c[%dC",0x1b,a);
}

void qclearln(){//clear from the current pos to end of ln
    printf("%c[K",0x1b);
}

void qhidecursor(){
    printf("%c[?25l",0x1b);
}

void qshowcursor(){
    printf("%c[?25h",0x1b);
}
