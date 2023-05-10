#ifndef INCLUDE_H
#define INCLUDE_H

using namespace std;

#include <mutex>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <filesystem>

//get basic variable
int getwidth();
int getheight();
int getbestScore();
bool getgameover();
int getnTail();
int getscore();

//function game loop
void Setup();
void Draw();
void Input();
void algorithm();

//set base
void setnTail(int size);
void setscore(int value);
void setgameover(bool state);

//function base
int load_best_score();
void centerConsoleWindow(int width, int height);
void save_best_score(int best_score);
void gotoxy(int x, int y);
void draw_menu();
bool process_menu();

#endif