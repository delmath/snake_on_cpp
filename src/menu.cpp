#include "../includes/include.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_menu(int selectedOption)
{
    int width = 50;
    int height = 20;

    system("cls");
    gotoxy(width / 2 - 7, 3);
    cout << "SNAKE only C++";;
    gotoxy(width / 2 - 3, 6);
    cout << "PLAY";
    gotoxy(width / 2 - 3, 8);
    cout << "MULTIPLAYER";
    gotoxy(width / 2 - 3, 10);
    cout << "QUIT";
    gotoxy(width / 2 - 4, 6);
    if (selectedOption == 0)
    {
        cout << ">";
    } else
    {
        cout << " ";
    }
    gotoxy(width / 2 - 9, 12);
    cout << "--- scoreboard ---";
    gotoxy(width / 2 - 7, 14);
    cout << "Last score: " << getscore();
    gotoxy(width / 2 - 7, 15);
    cout << "Best score: " << getbestScore();
}

bool process_menu()
{
    int width = 50;
    int height = 20;
    int selectedOption = 0;
    draw_menu(selectedOption);

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'o' || key == 'l')
            {
                gotoxy(width / 2 - 4, 6 + 2 * selectedOption);
                cout << " ";
                selectedOption = (selectedOption + 1) % 3;
                gotoxy(width / 2 - 4, 6 + 2 * selectedOption);
                cout << ">";
            }
            if (key == '\r')
            {
                if (selectedOption == 0)
                { // Single player
                    return false;
                } else if (selectedOption == 1)
                { // Multiplayer
                    // Add to host or join a game
                } else
                { // Quit
                    return true;
                }
            }
        }
        Sleep(10);
    }
}