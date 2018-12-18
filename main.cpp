#include <iostream>
#include "stdlib.h"
#include "conio.h"

using namespace std;

bool gameOver;
const int width = 25;
const int height = 15;
int x, y, fruitX, fruitY, score, length;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
const int maxLength = 30;
int tailX[maxLength];
int tailY[maxLength];
int cTailX[maxLength];
int cTailY[maxLength];
int prevX, prevY;
int prevCX, prevCY;
bool newGame = true;
bool rightKey;
int schw;

void Setup()
{
    schw = 0;
    gameOver = false;
    dir = STOP;
    x = width /2;
    y = height /2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    length = 1;
    rightKey = false;
    while(schw<1||schw>10){
        cout << "Geben sie eine Zahl von 1 - 10 fuer die Schwirigkeit an: ";
        cin >> schw;
        if(schw < 0 || schw > 10)
        {
            cout << "Falsche Schwirigkeit gewaehlt!";
            system("cls");
        }
    }
}

void Draw()
{
    system("cls");
    for(int counter2 = 0; counter2 < width+2; counter2++)
    {
        cout << "#";
    }
    cout << "\n";
    for(int counter = 0; counter < height; counter ++)
    {
        for(int counter2 = 0; counter2 < width; counter2++)
        {
            if (counter2 == 0)
            {
                cout << "#";
            }
             if(counter2 == x && counter == y)
            {
                cout << "O";
            }
            else if(counter == fruitY && counter2 == fruitX)
            {
                cout << "X";
            }
            else
            {
                bool print = false;
                for(int counter3 = 1; counter3 < length; counter3++)
                {
                    if(counter2 == tailX[counter3] && counter == tailY[counter3])
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                {
                    cout << " ";
                }
            }
        if(counter2 == width-1)
        {
            cout << "#\n";
        }

    }
}

    for(int l = 0; l < width+2; l++)
    {
        cout << "#";
    }

    for(int i = 0; i < 5; i++)
    {
        cout << "\n";
    }
    cout << x << "\n";
    cout << y << "\n";
    cout << "Score: " << score;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                if (dir == RIGHT)
                {
                    break;
                }
                dir = LEFT;
                break;
            case 'd':
                if(dir == LEFT)
                {
                    break;
                }
                dir = RIGHT;
                break;
            case 'w':
                if(dir == DOWN)
                {
                    break;
                }
                dir = UP;
                break;
            case 's':
                if(dir == UP)
                {
                    break;
                }
                dir = DOWN;
                break;
            case 'p':
                dir = STOP;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    prevX = x;
    prevY = y;
    tailX[0] = x;
    tailY[0] = y;
    for (int j = 1; j < length; j++)
    {
        prevCX = tailX[j];
        prevCY = tailY[j];
        tailX[j] = prevX;
        tailY[j] = prevY;
        prevX = prevCX;
        prevY = prevCY;
    }
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case STOP:
        y = y;
        x = x;
        break;
    }
     for (int o = 1; o < length ; o++)
    {
        if(x == tailX[o] && y == tailY[o])
        {
            gameOver = true;
        }
    }

    if(x >= width)
    {
        x = 0;
    }
    else if (x <0 )
    {
        x = width;
    }
    if (y >= height)
    {
        y = 0;
    }
    else if(y < 0)
    {
        y = height;
    }

    if(x == fruitX && y == fruitY)
    {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        length++;
    }
}

void NewGame()
{
    system("cls");
    cout << "Druecken sie 'y' fuer ein neues spiel und 'n' um abzubrechen.";
    while(!rightKey)
    {
        switch(_getch())
        {
        case 'y':
            newGame = true;
            rightKey = true;
            system("cls");
            break;
        case 'n':
            newGame = false;
            rightKey = true;
            break;
        }
    }
}

int main()
{
    while (newGame)
    {
        Setup();
            while(!gameOver)
            {
            Draw();
            Input();
            Logic();
            _sleep(500/schw);
        }
        NewGame();
    }
    return 0;
}
