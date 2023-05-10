#ifndef MULTI_GAME_H
#define MULTI_GAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <WinSock2.h>
#include "../includes/fruit.h"
#include "../includes/snake.h"

class MultiGame {
public:
    MultiGame();
    MultiGame(const std::string &hostAddress, unsigned short port);
    virtual ~MultiGame();

    void connect_to_game(const std::string &hostAddress, unsigned short port);
    void disconnect_from_game();
    void send_game_state();
    void receive_game_state();

protected:
    virtual void handle_received_game_state(const std::string &data);
    virtual void display_game_state();

private:
    Snake snake;
    Snake otherSnake;
    Fruit fruit;  
    SOCKET socket;
    bool isConnected;
    WSADATA wsaData;

    void start();
    void disconnect();

    void clear_screen();
    void sync_game_state();
    void game_loop();
};

#endif