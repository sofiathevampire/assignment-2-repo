#include "Tour.hpp"
#include <cmath>

Tour::Tour() {
    fitness = 0;
}

Tour::Tour(std::vector<City*> cities) {
    this->cities = cities;
    fitness = 0;
}

std::vector<City*> Tour::getCities() {
    return cities;
}

double Tour::getFitness() const {
    return fitness;
}

double Tour::setFitness(double fitness) {
    this->fitness = fitness;
}

bool Tour::containsCity(City* city) {
    for(City* currentCity : cities) {
        if(currentCity == city) {
            return true;
        } else {
            return false;
        }
    }
}

double Tour::getDistanceBetweenCities(City* city1, City* city2) {
    double xDifference = city1->getX() - city2->getX();
    double yDifference = city1->getY() - city2->getY();

    return sqrt((xDifference * xDifference) + (yDifference * yDifference));
}

double Tour::getTourDistance() {
    double totalDistance = 0;

    for(size_t i = 0; i < cities.size()-1; i++) {
        totalDistance += getDistanceBetweenCities(cities[i], cities[i+1]);

        // Returns to the starting city
        totalDistance += getDistanceBetweenCities(cities.back(), cities.front());
        return totalDistance;
    }
}

void Tour::determineFitness() {
    fitness = getTourDistance();
}