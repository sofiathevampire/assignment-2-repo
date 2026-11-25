#pragma once
#include "City.hpp"
#include <vector>

class Tour {
    private:
    std::vector<City*> cities;

    double fitness;

    public:
    Tour();
    Tour(std::vector<City*> cities);

    std::vector<City*> getCities();
    double getFitness() const;

    void setFitness(double fitness);
    bool containsCity(City* city);

    double getDistanceBetweenCities(City* city1, City* city2);
    double getTourDistance();
    void determineFitness();
};