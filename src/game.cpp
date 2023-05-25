#include "../includes/include.h"

int tailX[100], tailY[100]; //snake coordinates
int x, y, fruitX, fruitY;
enum eDirecton {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls
eDirecton dir;

void Setup()
{
    setgameover(false);
    dir = STOP;
    x = getwidth() / 2;
    y = getheight() / 2;
    fruitX = rand() % getwidth();
    fruitY = rand() % getheight();
    setscore(0);
}

void Draw()
{
    int width = getwidth();
    int height = getheight();

    if (getgameover()) {
        system("cls");
    }

    gotoxy(0, 0);

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; //WALL

            if (i == y && j == x)
                cout << "*"; //SNAKE

            else if (i == fruitY && j == fruitX)
                cout << "%"; //FRUIT

            else
            {
                bool print = false;

                for (int k = 0; k < getnTail(); k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "*";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << getscore() << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'q':
                dir = LEFT;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 'z':
                dir = UP;
                break;

            case 's':
                dir = DOWN ;
                break;

            case 'x':
                setgameover(true);
                break;
        }
    }
}

void algorithm()
{
    int prevX = tailX [0];
    int prevY = tailY [0];
    int prev2X, prev2Y;
    int width = getwidth();
    int height = getheight();

    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < getnTail(); i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y ;
    }

    switch (dir)
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

        default:
            break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        setgameover(true);

    for (int i = 0; i < getnTail(); i++)
        if (tailX[i] == x && tailY[i] == y)
            setgameover(true);

    if (x == fruitX && y == fruitY)
    {
        setscore(getscore() + 1);

        fruitX = rand() % width;
        fruitY = rand() % height;

        setnTail(getnTail() + 1);
    }
}