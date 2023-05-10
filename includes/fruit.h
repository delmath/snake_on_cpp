#ifndef FRUIT_H
#define FRUIT_H

class Fruit {
public:
    struct Position {
        int x, y;
    };

    Fruit();

    void generate_new_position();
    void set_position(int x, int y);
    Position get_position() const;

    void draw();

private:
    Position position;
};

#endif