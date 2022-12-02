#pragma once
int scanKeyboard();
int kbhit();
class Head
{
    public:
        void upmove();
        void downmove();
        void leftmove();
        void rightmove();
        int getx();
        int gety();
        int getdir();
        void changedir(int a);
        Head(int x,int y);
    private:
        int locx,locy,dir;
};
class Body
{
    public:
        void setx(int x);
        void sety(int y);
        void setloc(int x,int y);
        int getx();
        int gety();
        void act();
        bool ifact();
    private:
        int locx,locy;
        bool activated;
};