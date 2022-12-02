#include<iostream>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include"snake.h"
#define wall '+';
#define blank ' ';
#define head_gra '@';
#define body_gra '*';
using namespace std;
const int height=20;
const int width=40;
int scanKeyboard()
{
    int input;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings=stored_settings;
    new_settings.c_lflag &=(~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
    input=getchar();
    tcsetattr(0,TCSANOW,&stored_settings);
    return input;
}
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &=~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    oldf=fcntl(STDIN_FILENO,F_GETFL,0);
    fcntl(STDIN_FILENO,F_SETFL,oldf|O_NONBLOCK);
    ch=getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    fcntl(STDIN_FILENO,F_SETFL,oldf);
    if(ch!=EOF)
    {
        ungetc(ch,stdin);
        return 1;
    }
    return 0;
}
Head::Head(int x,int y)
{
    locx=x;
    locy=y;
}
void Head::upmove()
{
    locx--;
}
void Head::downmove()
{
    locx++;
}
void Head::leftmove()
{
    locy--;
}
void Head::rightmove()
{
    locy++;
}
void Head::changedir(int a)
{
    if(a=='w')
    dir=1;
    else if(a=='a')
    dir=2;
    else if(a=='s')
    dir=3;
    else if(a=='d')
    dir=4;
}
int Head::getx()
{
    return locx;
}
int Head::gety()
{
    return locy;
}
int Head::getdir()
{
    return dir;
}

void Body::setx(int x)
{
    locx=x;
}
void Body::sety(int y)
{
    locy=y;
}
void Body::act()
{
    activated=true;
}
int Body::getx()
{
    return locx;
}
int Body::gety()
{
    return locy;
}
void Body::setloc(int x,int y)
{
    locx=x;
    locy=y;
}
bool Body::ifact()
{
    return activated;
}