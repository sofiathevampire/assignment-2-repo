#pragma once

#include "City.hpp"
#include "Population.hpp"

class SingletonFacade
{
private:
    SingletonFacade();

    SingletonFacade(const SingletonFacade&) = delete;

    SingletonFacade& operator=(
        const SingletonFacade&
    ) = delete;

    void printTour(Tour tour);

public:
    static SingletonFacade& getInstance();
    void run();
};