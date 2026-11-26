#pragma once
#include "City.hpp"
#include <vector>

// Represents one possible route through all of the cities.
class Tour {
    private:
    // Stores all the cities in a specific order
    std::vector<City*> cities;

    // Total distance travelled of the route
    double fitness;

    public:
    // Constructors
    Tour();
    Tour(std::vector<City*> cities);

    // Returns vector of cities
    std::vector<City*> getCities();

    double getFitness();

    void setFitness(double fitness);

    // Checks if a city exists in the tour
    bool containsCity(City* city);

    // Calculates dist between 2 cities
    double getDistanceBetweenCities(City* city1, City* city2);

    // Calculates the total distance of the tour
    double getTourDistance();

    // Updates fitness using tour distance
    void determineFitness();

    void swapCities(int firstIndex, int secondIndex);
};