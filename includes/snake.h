#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

class Snake {
public:
    struct Position {
        int x, y;
    };

    Snake();

    void generate_initial_position();
    void set_position(int x, int y);
    Position get_position() const;

    void draw();

private:
    Position position;
};

#endif