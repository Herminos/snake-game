#include<iostream>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include"snake.h"
#define wall '+';
#define blank ' ';
#define head_gra '@';
#define body_gra '*';
using namespace std;
const int height=20;
const int width=40;
int map[20][40]={0};
bool foodif=true;
int score=0;
Head head(9,19);
Body body[30];
int bodynum=3;
void initialize()
{
    for(int i=0;i<height;i++)
    {
        map[i][0]=1;
        map[i][width-1]=1;
    }
    for(int i=0;i<width;i++)
    {
        map[0][i]=1;
        map[height-1][i]=1;
    }
    for(int i=1;i<height-1;i++)
    {
        for(int j=1;j<width-1;j++)
            if(map[i][j]!=3)
                map[i][j]=0;
    }
}
void print()
{
    cout<<"Your score is "<<score<<endl;
    if(map[head.getx()][head.gety()]==0)
        map[head.getx()][head.gety()]=2;
    if(map[head.getx()][head.gety()]==3)
        {
            map[head.getx()][head.gety()]=2;
            foodif=false;
            score++;
            bodynum++;
        }
    if(map[head.getx()][head.gety()]==1)
    {
        system("clear");
        cout<<"You lose!"<<endl;
        cout<<"Your final score is "<<score<<endl;
        exit(0);
    }
    for(int i=1;i<=bodynum;i++)
    {
        if(body[i].ifact()==true)
            map[body[i].getx()][body[i].gety()]=4;
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(map[i][j]==0)
                cout<<' ';
            if(map[i][j]==1)
                cout<<'+';
            if(map[i][j]==2)
                cout<<'@';
            if(map[i][j]==3)
                cout<<'#';
            if(map[i][j]==4)
                cout<<'*';
        }
        cout<<endl;
    }
}
void createfood()
{
    int x=rand()%18;
    int y=rand()%38;
    x++;
    y++;
    map[x][y]=3;
}
int main()
{
    srand((unsigned)time(NULL));
    cout<<"----------------------------------------"<<endl;
    cout<<"-                                      -"<<endl;
    cout<<"-  Welocome to play the snake game!!!  -"<<endl;
    cout<<"-     Use wasd to move your snake      -"<<endl;
    cout<<"-      Press any key to begin!!!       -"<<endl;
    cout<<"-                                      -"<<endl;
    cout<<"----------------------------------------"<<endl;
    body[1].setloc(9,20);
    body[2].setloc(9,21);
    body[3].setloc(9,22);
    body[1].act();
    body[2].act();
    body[3].act();
    initialize();
    createfood();
    head.changedir('w');
    if(scanKeyboard()!=0)
    while(true)
    {
        body[bodynum].act();
        body[bodynum].setloc(body[bodynum-1].getx(),body[bodynum-1].gety());
        body[1].setloc(head.getx(),head.gety());
        int x=body[1].getx();
        int y=body[1].gety();
        int m,n;
        for(int i=2;i<=bodynum;i++)
        {
            m=body[i].getx();
            n=body[i].gety();
            body[i].setloc(x,y);
            x=m;
            y=n;
        }
        if(foodif==false)
        {
            createfood();
            foodif=true;
        }
        if(kbhit()==1)
            head.changedir(scanKeyboard());
        if(head.getdir()==1)
            head.upmove();
        if(head.getdir()==2)
            head.leftmove();
        if(head.getdir()==3)
            head.downmove();
        if(head.getdir()==4)
            head.rightmove();
        print();
        initialize();
        sleep(1);
        system("clear");
    }
}