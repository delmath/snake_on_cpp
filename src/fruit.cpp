#include "../includes/fruit.h"

Fruit::Fruit() {
    // Initialize the fruit's position
}

Position Fruit::get_position() const {
    return position;
}

void Fruit::set_position(int x, int y) {
    position.x = x;
    position.y = y;
}

void Fruit::draw() {
    // Implement the draw for the fruit
}

void Fruit::generate_new_position() {
    // Generate a new position for the fruit
}
