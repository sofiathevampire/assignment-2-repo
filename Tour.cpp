#include "Tour.hpp"
#include <cmath>

// Default constructor, by default, fitness initialized to 0
Tour::Tour() {
    fitness = 0;
}

// Creates a tour given a list of cities
Tour::Tour(std::vector<City*> cities) {
    this->cities = cities;
    fitness = 0;
}

// Returns city's vector
std::vector<City*> Tour::getCities() {
    return cities;
}

double Tour::getFitness() {
    return fitness;
}

// Lets you manually set fitness value
void Tour::setFitness(double fitness) {
    this->fitness = fitness;
}

// Checks if a city already exists in tour
bool Tour::containsCity(City* city) {
    for(City* currentCity : cities) {
        if(currentCity == city) {
            return true;
        }
    }

    return false;
}

// Uses the formula for finding distance, which is
// the square root of (x2-x1)^2 + (y2-y1)^2
double Tour::getDistanceBetweenCities(City* city1, City* city2) {
    double xDifference = city1->getX() - city2->getX();
    double yDifference = city1->getY() - city2->getY();

    return sqrt((xDifference * xDifference) + (yDifference * yDifference));
}

// Calculates total length of the route
// Loops through all the cities, gets distance between a pair, sums it up
double Tour::getTourDistance() {
    double totalDistance = 0;

    for(int i = 0; i < cities.size()-1; i++) {
        totalDistance += getDistanceBetweenCities(cities[i], cities[i+1]);
    }

    totalDistance += getDistanceBetweenCities(cities.back(), cities.front());

    return totalDistance;
}

// Sets fitness to the total distance
void Tour::determineFitness() {
    fitness = getTourDistance();
}

void Tour::swapCities(int firstIndex, int secondIndex) {
    City* temporary = cities[firstIndex];

    cities[firstIndex] = cities[secondIndex];

    cities[secondIndex] = temporary;
}