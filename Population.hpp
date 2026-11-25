#pragma once
#include <vector>
#include "Tour.hpp"

class Population {
    private:
    std::vector<Tour> tours;

    public:
    Population();
    Population(std::vector<Tour> tours);
    std::vector<Tour>& getTours();

    Tour getBestTour();
    void determineFitness();
    void sortPopulation();
    Tour selectParent(int parentPoolSize);

    Tour crossover(Tour parent1, Tour parent2);

    void mutate(double mutationRate);
};