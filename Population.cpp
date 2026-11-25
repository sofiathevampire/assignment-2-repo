#include "Population.hpp"
#include <cstdlib>

Population::Population() {
}

Population::Population(std::vector<Tour> tours) {
    this->tours = tours;
}

std::vector<Tour>& Population::getTours() {
    return tours;
}

void Population::determineFitness() {
    for(int i=0; i < tours.size(); i++) {
        tours[i].determineFitness();
    }
}

void Population::sortPopulation() {
    for(int i = 0; i < tours.size(); i++) {
        for(int j = i + 1; j < tours.size(); j++) {
            if(tours[j].getFitness() < tours[i].getFitness()) {
                Tour temporary = tours[i];
                tours[i] = tours[j];
                tours[j] = temporary;
            }
        }
    }
}

Tour Population::getBestTour() {
    return tours[0];
}

Tour Population::selectParent(int parentPoolSize) {
    int randomIndex = rand() % tours.size();
    Tour bestTour = tours[randomIndex];

    for(int i = 1; i < parentPoolSize; i++) {
        randomIndex = rand() % tours.size();

        if(tours[randomIndex].getFitness() < bestTour.getFitness()) {
            bestTour = tours[randomIndex];
        }
    }
    return bestTour;
}

Tour Population::crossover(Tour parent1, Tour parent2) {
    std::vector<City*> childCities;

    int randomindex = rand() % parent1.getCities().size();

    for(int i = 0; i <= randomindex; i++) {
        childCities.push_back(parent1.getCities()[i]);
    }

    for(int i = 0; i < parent2.getCities().size(); i++) {
        City* city = parent2.getCities()[i];
        bool alreadyExists = false;

        for(int j = 0; j < childCities.size(); j++) {
            if(childCities[j] == city) {
                alreadyExists = true;
            }
        }

        if(!alreadyExists) {
            childCities.push_back(city);
        }
    }

    Tour child(childCities);
    child.determineFitness();
    return child;
}

// TODO: Implement the Mutate function