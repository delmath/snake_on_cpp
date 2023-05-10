#include "../includes/multi-game.h"

void clear_screen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

MultiGame::MultiGame(const std::string &hostAddress, short unsigned int port) {
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << "\n";
        exit(1);
    }

    socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == INVALID_SOCKET) {
        std::cerr << "socket creation failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        exit(1);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(hostAddress.c_str());
    serverAddress.sin_port = htons(port);

    if (connect(socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "connection failed: " << WSAGetLastError() << "\n";
        closesocket(socket);
        WSACleanup();
        exit(1);
    }

    isConnected = true;
}

void MultiGame::disconnect() {
    closesocket(socket);
    isConnected = false;
}

void MultiGame::connect_to_game(const std::string &hostAddress, short unsigned int port) {
    disconnect();
    socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == INVALID_SOCKET) {
        std::cerr << "socket creation failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        exit(1);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(hostAddress.c_str());
    serverAddress.sin_port = htons(port);

    if (connect(socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "connection failed: " << WSAGetLastError() << "\n";
        closesocket(socket);
        WSACleanup();
        exit(1);
    }

    isConnected = true;
}

void MultiGame::disconnect_from_game() {
    closesocket(socket);
    isConnected = false;
}

void MultiGame::send_game_state() {
    std::stringstream ss;
    ss << snake.get_position().x << "," << snake.get_position().y << ","
       << fruit.get_position().x << "," << fruit.get_position().y;
    std::string data = ss.str();

    send(socket, data.c_str(), data.size(), 0);
}

void MultiGame::receive_game_state() {
    char buffer[1024] = { 0 };
    int bytesReceived = recv(socket, buffer, 1024, 0);
    if (bytesReceived <= 0) {
        // Handle error
    }
    std::string receivedData(buffer, bytesReceived);
    handle_received_game_state(receivedData);
}

void MultiGame::handle_received_game_state(const std::string &data) {
    std::stringstream ss(data);
    std::string token;
    int x, y;
    std::getline(ss, token, ',');
    x = std::stoi(token);
    std::getline(ss, token, ',');
    y = std::stoi(token);
    otherSnake.set_position(x, y);
    std::getline(ss, token, ',');
    x = std::stoi(token);
    std::getline(ss, token, ',');
    y = std::stoi(token);

    fruit.set_position(x, y);
}

void MultiGame::display_game_state() {
    clear_screen();
    snake.draw();
    fruit.draw();
    
    std::cout << "Utilisez les touches directionnelles pour déplacer le serpent." << std::endl;
}

void MultiGame::sync_game_state() {
    send_game_state();
    receive_game_state();
}

void MultiGame::start() {
    snake.generate_initial_position();
    fruit.generate_new_position();
    game_loop();
    disconnect();
}

void MultiGame::game_loop() {
    while (isConnected) {
        sync_game_state();
        display_game_state();
    }
}