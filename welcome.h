#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

COORD coord= {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void welcome_msg()
{
    cout<<"------------------------------------------------------------------------------------------------------------------------";
    gotoxy(50,1);
    cout<<"welcome to";
    gotoxy(48,2);
    cout<<"THE RAT MAZE GAME";
    cout<<"\n------------------------------------------------------------------------------------------------------------------------";

}


