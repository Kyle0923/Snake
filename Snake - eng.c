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
/**Game map is the map array to be shown on the screen*/
const int HEIGHTS=16, WIDTHS=31;//Heights=Y-1£»Widths=X-1
SNAKE TheSnake[17*32];//snake array, each element contains the info of one unit of the snake
SNAKE food={0,0,'$'};//to be eaten
int BodyLength=5;//actual length = bodylength+1
void SnakeMove(int direction);//to move the snake
void PrintMap();//show the GameMap on the screen
int checkborder(int);//return 1 when hits the border
int checkbody(SNAKE, int);//return 1 when hits the body
void checkfood();//when eaten, bodylength+1, generate another food
int godmode=0;//godmode = cheating


int main()
{
    int i,j;
    int dir,temp;
    int delay=300;//unit£ºns, the smaller, the faster
    system("title=Snake");
    printf("**Game Manual£º**\n\nSupport ¡ü¡ý¡û¡ú, WASD, number key 8246.\nHold the key or double press the key can speed up.\nReturn to original speed when you change direction\nPress space to pause.\n\n\\\\Press 'g' can turn on 'GodMode'//\n¡ü¡üNo boundary, can go across the body, extra points when hits the food.¡ü¡ü\n\n");
    printf("Press any key to start...");
    getch();
    /***seems we don't need this anymore
    for (i = 0;i<=HEIGHTS;i++)//initialize game map 2-D array
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            GameMap[i][j]='.';
            //printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    */
    //printf("\n-------\n");
    srand(time(0));
    for (i=0;i<=(HEIGHTS+1)*(WIDTHS+1)-1;i++) //initialize the snake
    {
        TheSnake[i]=(SNAKE) {-1,-1,'o'};
    }
    TheSnake[0].shape='@';
    TheSnake[0].Sx=rand()%(WIDTHS-BodyLength-3)+3;//initial X (random) of the head
    TheSnake[0].Sy=rand()%(HEIGHTS-BodyLength-3)+3;//initial Y (random) of the head

    //generate food
    food.Sx=rand()%(WIDTHS);
    food.Sy=rand()%(HEIGHTS);

    //initialize snake body, randomly go down or right by 1
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
    dir='w';//default direction, goes up
    i=0;//use as counter now
    while (1)
    {
        while(kbhit())
        {
            temp=getch();
            if (temp=='g'){godmode=!godmode;}//godmode toggles
            if (temp=='0'){godmode=-1;}
            if (temp==32){printf("PAUSE");temp=getch();}//hit space to pause
            if (temp==dir)//temp==direction: speed up
            {
                i=(delay/50-1);
            }
            else
            {
                if (temp==77 || temp==75 || temp==80 || temp==72 || temp=='6' || temp=='4' || temp=='8' || temp=='2' || temp=='d' || temp=='a' || temp=='w' || temp=='s')//valid key
                {
                    if (!(((dir==77||dir=='6'||dir=='d')&&(temp==75||temp=='4'||temp=='a'))||((dir==75||dir=='4'||dir=='a')&&(temp==77||temp=='6'||temp=='d'))
                          ||((dir==80||dir=='2'||dir=='s')&&(temp==72||temp=='8'||temp=='w'))||((dir==72||dir=='8'||dir=='w')&&(temp==80||temp=='2'||temp=='s'))))//invalid direction
                    {i=0;
                    dir=temp;//set direction to the new input
                    SnakeMove(dir);//move snake
                    PrintMap();
                    if (checkborder(godmode)||checkbody(TheSnake[0],godmode))//if either is true, game over
                        break;
                    _sleep(delay);}//program pause for 'delay' nano sec
                }
                else{if (i>0){i--;}}
            }
        }
        if (checkborder(godmode)||checkbody(TheSnake[0],godmode))//if either is true, game over
            break;//break the loop, exit the program
        SnakeMove(dir);
        PrintMap();
        if (checkborder(godmode)||checkbody(TheSnake[0],godmode))
            break;
        _sleep(delay-50*i);
        if (i>0){i--;}
    }
    printf("You LOST!\nPress Esc to exit...");
    while(getch()!=27);//hit esc to exit
    return;
}

void SnakeMove(int direction)
{

    //if (direction==77 || direction==75 || direction==80 || direction==72 || direction=='6' || direction=='4' || direction=='8' || direction=='2' || direction=='d' || direction=='a' || direction=='w' || direction=='s')/don't need anymore
    //{
        int i;
        for (i=BodyLength;i>=1;i--)
        {
            TheSnake[i].Sx=TheSnake[i-1].Sx;
            TheSnake[i].Sy=TheSnake[i-1].Sy;//each body element goes to the one prior to it
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
        //default: {printf("Invalid\ndir=%c\n",direction);getch();break;}
        }
        checkfood();//check if eats food
    //}
    return;
}

void PrintMap()
{
    system("cls");//clear console
    int i,j,s;//i,j: counters for map, s: counter for snake
    for (i = 0;i<=HEIGHTS;i++)
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            GameMap[i][j]='.';
            if (food.Sx==j&&food.Sy==i)//insert the food
                {GameMap[i][j]=food.shape;}
            for (s = BodyLength;s>=0;s--)//run through the snake
            {
                if (TheSnake[s].Sx==j&&TheSnake[s].Sy==i)//if the point is snake
                {
                    GameMap[i][j]=TheSnake[s].shape;//insert snake shape to the map
                }
            }
            printf("%c",GameMap[i][j]);//print out the map
        }
        printf("\n");
    }
    //for (s = 0;s<=BodyLength;s++)
    //printf("Body[%d]'s x=%d y=%d\n",s,TheSnake[s].Sx,TheSnake[s].Sy);
    printf("Your score is %d.\n",BodyLength);
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
    if (TheSnake[0].Sx==food.Sx&&TheSnake[0].Sy==food.Sy)//if coordinates match, food is "eaten"
    {
        BodyLength+=1+godmode*25;
        /***Regenerate the food*/
        food.Sx=rand()%(WIDTHS);
        food.Sy=rand()%(HEIGHTS);
        while(checkbody(food,0))//check if the food is inside the body
        {
            //if true generate again
            food.Sx=rand()%(WIDTHS);
            food.Sy=rand()%(HEIGHTS);
        }
    }
    return;
}
