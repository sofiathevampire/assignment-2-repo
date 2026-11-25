#pragma once
#include <string>

class City {
    private:
    std::string name;
    int x;
    int y;

    public:
    City(std::string name, int x, int y);
    std::string getName();
    int getX();
    int getY();
};