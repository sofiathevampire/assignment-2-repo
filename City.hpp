#pragma once
#include <string>

// Represents one city.
class City {
    private:
    // Name of city, x coord, y coord.
    std::string name;
    int x;
    int y;

    public:
    City(std::string name, int x, int y);

    // Returns the Name of the city.
    std::string getName();

    // Returns the x coord, y coord, respectively.
    int getX();
    int getY();
};