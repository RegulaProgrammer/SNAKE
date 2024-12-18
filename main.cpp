#include <iostream>
#include <windows.h>
#include <conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

int body[200][2];
int n = 1;
int body_size = 4;
int x = 10;
int y = 12;
int dir = 3;
int xf = 30;
int yf = 15;
int speed = 100;
int h = 1;
int score1 = 0;
int score2 = 0;

char key_press;

void gotoxy(int x, int y) //Posicionar el cursor
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void pLine()
{
    for(int i = 2; i < 117; i++){
        gotoxy(i, 1); printf("%c", 205);
        gotoxy(i, 28); printf("%c", 205);
    }

    for(int i = 2; i < 28; i++){
        gotoxy(2, i); printf("%c", 186);
        gotoxy(117, i); printf("%c", 186);
    }
    gotoxy(2,1); printf("%c",201);
    gotoxy(2,28); printf("%c",200);
    gotoxy(117,1); printf("%c",187);
    gotoxy(117,28); printf("%c",188);
}

void set_Position()
{
    body[n][0] = x;
    body[n][1] = y;
    n++;
    if(n == body_size) n = 1;

}

void make_body()
{
    for(int i=1; i<body_size; i++){
        gotoxy(body[i][0],body[i][1]); printf("*");
    }
}

void delete_body()
{
    gotoxy(body[n][0],body[n][1]); printf(" ");
}

void food()
{
    if(x == xf && y == yf){
        xf = (rand()%110)+4;
        yf = (rand()%20)+4;

        body_size++;
        score2++;
        gotoxy(xf,yf); printf("%c",4);

    }
}

void controller()
{
    if(kbhit()){
            key_press = getch();

            switch(key_press)
            {
                case ARRIBA:
                    if(dir != 2)
                        dir = 1;
                        break;
                case ABAJO:
                    if(dir != 1)
                        dir = 2;
                        break;
                case DERECHA:
                    if(dir != 4)
                        dir = 3;
                        break;
                case IZQUIERDA:
                    if(dir != 3)
                        dir = 4;
                        break;
            }
        }

}

void points()
{
    gotoxy(3, 29); printf("SCORE %d%d",score1,score2);

    if(score2>9){
        score2 = 0;
        score1++;
    }
}

void sonic()
{
    if(score1 == h*2)
        speed -=10;
        h++;
}

bool game_over()
{
    if(y==1||y==28||x==2||x==117) return true;

    for(int i = body_size -1; i>0; i--){
        if(body[i][0]==x && body[i][1]==y)
            return true;
    }

    return false;
}

int main()
{
    system("title SNAKE");
    system("color 02");
    pLine();
    gotoxy(xf,yf); printf("%c",4);

    while(key_press != ESC && !game_over())
    {
        delete_body();
        set_Position();
        make_body();
        food();
        points();
        sonic();
        controller();
        controller();

        if(dir == 1) y--;
        if(dir == 2) y++;
        if(dir == 3) x++;
        if(dir == 4) x--;

        Sleep(speed);
    }
    system("color 74");
    pLine();
    system("pause>null");
    return 0;
}
