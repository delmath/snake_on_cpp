#include "../includes/include.h"

bool gameover;
const int width = 50;
const int height = 50;
int lastScore = 0;
int bestScore = 0;
int score = 0;
int nTail;
const int XOR_KEY = 0xAB;

int getwidth() {return  width;}
int getheight() {return height;}
int getlastScore()  {return lastScore;}
int getbestScore()  {return bestScore;}
int getnTail()  {return nTail;}
int getscore()  {return score;}
bool getgameover()  {return gameover;}

void setnTail(int size)   {nTail = size;}
void setgameover(bool state)   {gameover = state;}
void setscore(int value)    {score = value;}

void centerConsoleWindow(int width, int height)
{
    HWND consoleWindow = GetConsoleWindow();
    RECT screenRect;
    GetWindowRect(GetDesktopWindow(), &screenRect);

    int x = (screenRect.right - width) / 2;
    int y = (screenRect.bottom - height) / 2;

    MoveWindow(consoleWindow, x, y, width, height, TRUE);
}

int main()
{
    bestScore = load_best_score();

    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU));
    ShowWindow(console, SW_MAXIMIZE);

    while (true)
    {
        if (score > bestScore)
        {
            bestScore = score;
            save_best_score(bestScore);
        }

        if (process_menu())
        {
            break;
        }

        Setup();
        gameover = false;
        while (!gameover)
        {
            Draw();
            Input();
            algorithm();
            Sleep(1);
        }
    }
    return 0;
}