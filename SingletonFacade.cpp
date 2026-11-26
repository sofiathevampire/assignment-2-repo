#include "SingletonFacade.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Constructor for the SingletonFacade; Is private so only 
// one instance can be created.
SingletonFacade::SingletonFacade()
{
}

// Number of cities that will exist in each tour
const int CITIES_IN_TOUR = 32;
// Number of tours that will exist in the population
const int POPULATION_SIZE = 32;
// Number of random swaps used to shuffle a tour
const int SHUFFLES = 64;
// Maximum number of algorithm iterations
const int ITERATIONS = 1000;
// Largest x or y coord for a city
const int MAP_BOUNDARY = 1000;
// Number of tours randomly examined for parent selection
const int PARENT_POOL_SIZE = 5;
// Probability of a city mutating
const double MUTATION_RATE = 0.15;
// Number of parents used in crossover
const int NUMBER_OF_PARENTS = 2;
// Number of elite tours kept for each generation
const int NUMBER_OF_ELITES = 1;
// The improvement factor to reach before the algorithm stops
const double IMPROVEMENT_FACTOR = 1.2;

// The object is only created once when the function is called
SingletonFacade& SingletonFacade::getInstance() {
    static SingletonFacade instance;

    return instance;
}

// Prints a tour and its distance
void SingletonFacade::printTour(Tour tour) {
    // Gets the vector of cities from the tour
    std::vector<City*> cities = tour.getCities();

    std::cout << "Distance: " << tour.getFitness() << std::endl;
    std::cout << "(";

    // Loop through each city, print name
    for(int i = 0; i < cities.size(); i++) {
        std::cout << cities[i]->getName() << "->";
    }

    // If at least one city exists, print the first city again;
    // To show how the salesperson returns back to the starting city
    if(!cities.empty()) {
        std::cout << cities[0]->getName();
    }

    std::cout << ")" << std::endl;
}

// Runs the genetic algorithm
void SingletonFacade::run() {
    // Seeds the random number generator using the current time
    srand(time(nullptr));

    // Is used to store all of the cities created by our program
    std::vector<City> cities;

    // Creates all of the cities for the algorithm; ex. City1, City6
    for(int i = 0; i < CITIES_IN_TOUR; i++){
        std::string cityName = "City" + std::to_string(i + 1);

        int x = rand() % (MAP_BOUNDARY + 1); // X can only be between 0 and the map_boundary

        int y = rand() % (MAP_BOUNDARY + 1);

        cities.push_back(City(cityName, x, y)); // Adds each city to the list of cities
    }

    // Is used to store pointers to all the cities
    std::vector<City*> cityPointers;

    // Visits all of the cities we created and stores the address of each city
    for(int i = 0; i < cities.size(); i++) {
        cityPointers.push_back(&cities[i]);
    }

    // Stores all of the tours that will be placed into the population
    std::vector<Tour> tours;

    // Creates the number of tours required
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        // Starts off by having all of the cities in their original order
        std::vector<City*> shuffledCities = cityPointers;

        // This is used to shuffle all of the cities using random swaps
        for(int j = 0; j < SHUFFLES; j++) {
            // Picks a random first & second position
            int firstIndex =
                rand() % shuffledCities.size();

            int secondIndex =
                rand() % shuffledCities.size();

            // Temporarily saves the first city
            City* temporary =
                shuffledCities[firstIndex];

            // Moves the second city into the first position
            shuffledCities[firstIndex] =
                shuffledCities[secondIndex];

            // Moves the original first city into the second position
            shuffledCities[secondIndex] =
                temporary;
        }

        // Creates a brand new tour using the shuffled cities, adds to the collection of tours
        tours.push_back(Tour(shuffledCities));
    }

    // Creates a population with all the tours we generated
    Population population(tours);
    // Calculates the fitness of all the tours,
    // sorts them from best fitness to worst fitness
    population.determineFitness();

    population.sortPopulation();
    // The best tour becomes the starting elite tour
    Tour baseTour = population.getBestTour();
    // Also keeps track of the best tour
    Tour bestTour = baseTour;

    // Stores the original distance
    double baseDistance = baseTour.getFitness();
    // Stores the best distance found so far
    double bestDistance = baseDistance;

    std::cout << "Original elite: " << std::endl;

    printTour(baseTour);

    std::cout << "\n--- STARTING ALGORITHM ---\n";

    // Counts the number of generations
    int iteration = 0;

    // According to instructions; Continue until
    // we reached the maximum iterations, or until we've reached the wanted amount of improvement
    while(iteration < ITERATIONS && baseDistance / bestDistance <= IMPROVEMENT_FACTOR) {
        // We want to remember the previous best so we know if a new elite appears
        double previousBest = bestDistance;

        // make sure the population is sorted
        population.sortPopulation();
        // stores the next generation of tours
        std::vector<Tour> newTours;

        // We copy the elite tours into the next generation
        for(int i = 0; i < NUMBER_OF_ELITES; i++) {
            newTours.push_back(population.getTours()[i]);
        }

        // Continues creating children until the newTours is equal to the necessary number of children
        // Note: newTours just contains the Elite tour
        while(newTours.size()<POPULATION_SIZE) {
            // Select a parent from the population
            Tour child = population.selectParent(PARENT_POOL_SIZE);

            // Selects more parents and performs crossover
            for(int i = 1; i < NUMBER_OF_PARENTS; i++)
            {
                // Selects another parent
                Tour parent = population.selectParent(PARENT_POOL_SIZE);

                // Creates a child combining the 2 parents
                child = population.crossover(child, parent);
            }

            // Adds the newly recombined child into the new population
            // so now newTours contains the elite and the child
            newTours.push_back(child);
        }

        // Replaces the old population with the newly generated population
        // so now the new population is just the elite and all of the children.
        population.getTours() = newTours;

        // Randomly mutates some tours & recalculates their fitness beacuse some
        // of the tours may have changed.
        population.mutate(MUTATION_RATE);

        population.determineFitness();

        // Sorts from shortest to largest distances
        // best tour is at the front
        population.sortPopulation();

        // Save the best tour, and the elite distance
        bestTour = population.getBestTour();

        bestDistance = bestTour.getFitness();

        // Prints the number of the current generation
        std::cout << "\nIteration: " << iteration << std::endl;

        // Checks for a new elite
        if(bestDistance < previousBest) {
            std::cout << "NEW ELITE FOUND:" << std::endl;

            std::cout << "Distance: " << bestDistance << std::endl;
        }
        else {
            std::cout << "Elite distance: " << bestDistance << std::endl;
            // Prints the second best tour if no new elite was found
            std::cout << "Best non-elite distance: " << population.getTours()[1].getFitness() << std::endl;
        }

        std::cout << "Improvement over base: "
            << baseDistance / bestDistance
            << std::endl;

        iteration++; 
    }

    std::cout << "\n--- FINISHED ALGORITHM ---\n";

    std::cout
        << "Total iterations: "
        << iteration
        << std::endl;

    std::cout
        << "\nOriginal elite:\n";

    printTour(baseTour);

    std::cout
        << "\nBest elite:\n";

    printTour(bestTour);

    // Calculates how much the best tour improved compared to the original elite tour
    double improvement = baseDistance / bestDistance;

    // Checks to see if we achieved our improvement factor or not
    if(improvement > IMPROVEMENT_FACTOR) {
        std::cout << "\nImprovement factor reached!" << std::endl;
    }
    else {
        std::cout
            << "\nImprovement factor not reached."
            << std::endl;
    }

    std::cout
        << "Improvement factor: "
        << improvement
        << std::endl;
}