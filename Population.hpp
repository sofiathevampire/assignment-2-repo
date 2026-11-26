#pragma once
#include <vector>
#include "Tour.hpp"

// Represents a collection of tours
// Performs sorting, crossovers, and mutations
class Population {
    private:
    // Stores all tours in the population
    std::vector<Tour> tours;

    public:
    // Default constructor
    Population();

    // Constructor that accepts a vector of tours
    Population(std::vector<Tour> tours);

    // Returns the collection of routes/tours; uses ref. because we want to access the actual vector of tours, not a copy
    std::vector<Tour>& getTours();

    // Returns the best tour in the population
    Tour getBestTour();

    // Calculates the fitness for every tour
    void determineFitness();

    // Sorts tours from best fitness to worst fitness
    void sortPopulation();

    Tour selectParent(int parentPoolSize);

    Tour crossover(Tour parent1, Tour parent2);

    // Mutates tours using a mutation rate
    void mutate(double mutationRate);
};