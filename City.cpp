#include "City.hpp"



City::City(std::string name, int x, int y) {
    this->name = name;
    this->x = x;
    this->y = y;
}

std::string City::getName() {
    return name;
}

int City::getX() {
    return x;
}

int City::getY() {
    return y;
}