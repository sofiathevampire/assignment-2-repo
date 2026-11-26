#include "Population.hpp"
#include <cstdlib>

// Default constructor
Population::Population() {
}

// Assigns the collection of tours in a population
Population::Population(std::vector<Tour> tours) {
    this->tours = tours;
}

// Returns all the tours in the population
std::vector<Tour>& Population::getTours() {
    return tours;
}

// Calculates the fitness for each individual tour
void Population::determineFitness() {
    for(int i=0; i < tours.size(); i++) {
        tours[i].determineFitness();
    }
}

// Sorts the tours from shortest fitness to greatest fitness
void Population::sortPopulation() {
    // Starts at the first tour in the population
    for(int i = 0; i < tours.size(); i++) {

        // Compares the current tour with every tour that comes after it
        for(int j = i + 1; j < tours.size(); j++) {

            // If the tour at position j has better fitness/a shorter distance
            // than the tour at position i, we want to swap them
            // Essentially swapping them, so they are in order
            if(tours[j].getFitness() < tours[i].getFitness()) {
                Tour temporary = tours[i]; // Temporarily store the smaller distance
                tours[i] = tours[j]; // Sets the lower index to the smaller value
                tours[j] = temporary; // Sets higher index to larger value
            }
        }
    }
}

// Since we already sorted it, the best tour is at index 0
Tour Population::getBestTour() {
    return tours[0];
}

// Chooses a parent tour to make child tours
Tour Population::selectParent(int parentPoolSize) {
    int randomIndex = 1 + rand() % (tours.size() - 1);

    // We assume that some randomly selected parent tour is currently the best
    Tour bestTour = tours[randomIndex]; // ex. tours[5]

    // Loops through a given number of random tours; ex. 3
    // Compares these random tours from the population till it finds the best one
    for(int i = 1; i < parentPoolSize; i++) {
        randomIndex = rand() % tours.size();

        if(tours[randomIndex].getFitness() < bestTour.getFitness()) {
            bestTour = tours[randomIndex];
        }
    }
    return bestTour;
}

// Creates a child tour by combining two parent tours
Tour Population::crossover(Tour parent1, Tour parent2) {

    // A vector that will eventually store the cities which make up the child tour
    std::vector<City*> childCities;

    // Chooses a random crossover point; ex.choosing index 2 means ABC from Parent 1's ABCDE
    int randomindex = rand() % parent1.getCities().size();

    // Puts all of the cities from Parent 1 into the list of cities
    for(int i = 0; i <= randomindex; i++) {
        childCities.push_back(parent1.getCities()[i]);
    }

    // Loops through all of the cities in Parent2
    // We store the current city from Parent2, and assume this city doesn't
    // already exist in the child tour.
    for(int i = 0; i < parent2.getCities().size(); i++) {
        City* city = parent2.getCities()[i];
        bool alreadyExists = false;

        // Loops through current child cities & makes sure we don't
        // add in cities from Parent 2 that already exist in the child
        for(int j = 0; j < childCities.size(); j++) {
            if(childCities[j] == city) {
                alreadyExists = true;
            }
        }

        if(!alreadyExists) {
            childCities.push_back(city);
        }
    }
// Creates a brand new Tour object for the child & returns this child tour
    Tour child(childCities);
    child.determineFitness();
    return child;
}

// Randomly modifies some of the tours to introduce variation
void Population::mutate(double mutationRate) {

    // Loops through every tour in the population starting at index 1 because index 0 is the elite tour
    for(int i = 1; i < tours.size(); i++) {
        // Random from 0 to 99
        int roll = rand() % 100;

        // Only 30% of tours should be mutated, so if the
        // roll greater than 30, we should skip
        // this tour and move on to the next.
        if(roll >= 30) {
            continue;
        }

        // Num cities in current tour
        int cityCount = tours[i].getCities().size();

        // Loop through each city in the current tour; stop early at -1 beacuse
        // we are comparing with city that comes after it.
        for(int j = 0; j < cityCount - 1; j++) {
            // Random decimal from 0 to 1
            double randomValue = static_cast<double>(rand()) / RAND_MAX;

            // If the random value is less than the mutation rate, mutate
            if(randomValue < mutationRate) {
                tours[i].swapCities(
                    j,
                    j + 1
                );
                // the mutation just swaps the city with the one after it
            }
        }

        // Recalculate fitness of this tour because we've changed it
        tours[i].determineFitness();
    }
}