#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct
{
    int Sx;
    int Sy;
    char shape;
}SNAKE;

char GameMap[17][32]; //[HEIGHT][WIDTHS]
const int HEIGHTS=16, WIDTHS=31;//Heights=纵轴-1；Widths=横轴-1
SNAKE TheSnake[17*32];
SNAKE food={1,1,'$'};
int BodyLength=5;//actual length = bodylength+1
void SnakeMove(int direction);
void PrintMap();
int checkborder(int);
int checkbody(SNAKE, int);
void checkfood();
int godmode=0;


int main()
{
    int i,j;
    int dir,temp;
    int delay=300;//单位：毫秒，数值越小速度越快
    system("title=贪吃蛇");
    printf("**游戏手册：**\n\n支持上下左右、WASD、小键盘4628。\n连续点同一方向可以加速，换方向后回到原来速度。\n\n\\\\按g可进入godmode -- 无边界，可以穿过蛇身，吃一颗食物身长+25//\n\n");
    printf("按任意键开始游戏...");
    getch();
    for (i = 0;i<=HEIGHTS;i++)
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            GameMap[i][j]='.';
            //printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    //printf("\n-------\n");
    srand(time(0));
    for (i=0;i<=(HEIGHTS+1)*(WIDTHS+1)-1;i++)
    {
        TheSnake[i]=(SNAKE) {-1,-1,'o'};
    }
    TheSnake[0].shape='@';
    TheSnake[0].Sx=rand()%(WIDTHS-BodyLength-3)+3;
    TheSnake[0].Sy=rand()%(HEIGHTS-BodyLength-3)+3;
    //
    TheSnake[0].Sx=rand()%(WIDTHS-0-3)+3;
    TheSnake[0].Sy=rand()%(HEIGHTS-0-3)+3;
    //
    food.Sx=rand()%(WIDTHS);
    food.Sy=rand()%(HEIGHTS);
    for (i=1;i<=BodyLength;i++)
    {
        if (rand()%2)
        {
            TheSnake[i].Sx=TheSnake[i-1].Sx+1;
            TheSnake[i].Sy=TheSnake[i-1].Sy;
        }
        else
        {
             TheSnake[i].Sy=TheSnake[i-1].Sy+1;
             TheSnake[i].Sx=TheSnake[i-1].Sx;
        }
    }
    PrintMap();
    dir='w';
    i=0;
    while (1)
    {
        while(kbhit())
        {
            temp=getch();
            if (temp=='g'){godmode=!godmode;}
            if (temp=='0'){godmode=-1;}
            if (temp==dir)
            {
                i=(delay/50-1);
            }
            else
            {
                if (temp==77 || temp==75 || temp==80 || temp==72 || temp=='6' || temp=='4' || temp=='8' || temp=='2' || temp=='d' || temp=='a' || temp=='w' || temp=='s')
                {
                    if (!(((dir==77||dir=='6'||dir=='d')&&(temp==75||temp=='4'||temp=='a'))||((dir==75||dir=='4'||dir=='a')&&(temp==77||temp=='6'||temp=='d'))
                          ||((dir==80||dir=='2'||dir=='s')&&(temp==72||temp=='8'||temp=='w'))||((dir==72||dir=='8'||dir=='w')&&(temp==80||temp=='2'||temp=='s'))))
                    {i=0;
                    dir=temp;
                    SnakeMove(dir);
                    PrintMap();
                    if (checkborder(godmode)||checkbody(TheSnake[0],godmode))
                        break;
                    _sleep(delay);}
                }
                else{if (i>0){i-=0.5;}}
            }
        }
        if (checkborder(godmode)||checkbody(TheSnake[0],godmode))
            break;
        SnakeMove(dir);
        PrintMap();
        if (checkborder(godmode)||checkbody(TheSnake[0],godmode))
            break;
        _sleep(delay-50*i);
        if (i>0){i--;}
    }
    printf("你输了!\n按Esc退出游戏...");
    while(getch()!=27);
    return;
}

void SnakeMove(int direction)
{
    if (direction==77 || direction==75 || direction==80 || direction==72 || direction=='6' || direction=='4' || direction=='8' || direction=='2' || direction=='d' || direction=='a' || direction=='w' || direction=='s')
    {
        int i;
        for (i=BodyLength;i>=1;i--)
        {
            TheSnake[i].Sx=TheSnake[i-1].Sx;
            TheSnake[i].Sy=TheSnake[i-1].Sy;
        }
        switch(direction)
        {
        case 77: case '6': case'd'://right
            {TheSnake[0].Sx=TheSnake[0].Sx+1;break;}
        case 75: case '4': case'a'://left
            {TheSnake[0].Sx=TheSnake[0].Sx-1;break;}
        case 80: case '2': case's'://down
            {TheSnake[0].Sy=TheSnake[0].Sy+1;break;}
        case 72: case '8': case'w'://up
            {TheSnake[0].Sy=TheSnake[0].Sy-1;break;}
        //default: {printf("No!!!!\nd=%d\n",direction);getch();break;}
        }
        checkfood();
    }
    return;
}

void PrintMap()
{
    system("cls");
    int i,j,s;
    for (i = 0;i<=HEIGHTS;i++)
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            GameMap[i][j]='.';
            if (food.Sx==j&&food.Sy==i)
                {GameMap[i][j]=food.shape;}
            for (s = BodyLength;s>=0;s--)
            {
                if (TheSnake[s].Sx==j&&TheSnake[s].Sy==i)
                {
                    GameMap[i][j]=TheSnake[s].shape;
                }
            }
            printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    //for (s = 0;s<=BodyLength;s++)
    //printf("Body[%d]'s x=%d y=%d\n",s,TheSnake[s].Sx,TheSnake[s].Sy);
    printf("你的得分是%d。\n",BodyLength);
    if (godmode)
        printf("Godmode is on\n");
    return;
}

int checkborder(int mode)
{
    if (!mode)
    {if (TheSnake[0].Sx>WIDTHS || TheSnake[0].Sy>HEIGHTS||TheSnake[0].Sx<0 || TheSnake[0].Sy<0)
        {return 1;}}
    return 0;
}

int checkbody(SNAKE head, int mode)
{
    if (!mode)
    {int s;
    for (s = 1;s<=BodyLength;s++)
    {
        if (head.Sx==TheSnake[s].Sx&&head.Sy==TheSnake[s].Sy)
            {return 1;}
    }
    }
    return 0;
}

void checkfood()
{
    if (TheSnake[0].Sx==food.Sx&&TheSnake[0].Sy==food.Sy)
    {
        BodyLength+=1+godmode*25;//每吃一个食物蛇增加的长度
        food.Sx=rand()%(WIDTHS);
        food.Sy=rand()%(HEIGHTS);
        while(checkbody(food,0))
        {
            food.Sx=rand()%(WIDTHS);
            food.Sy=rand()%(HEIGHTS);
        }
    }
    return;
}
