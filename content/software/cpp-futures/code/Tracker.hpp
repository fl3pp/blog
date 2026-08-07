#include <cstdlib>
#include <iostream>
#include <syncstream>

#pragma once

struct Tracker
{
    int id{rand() % 100};
    bool is_moved_from{false};

    Tracker()
    {
        std::cout << "constructed " << id << '\n';
    }

    void operator()() const
    {
        std::cout << "operator() called on " << id << '\n';
    }

    Tracker(Tracker&& other)
    {
        id = other.id;
        other.is_moved_from = true;
        std::cout << "moved " << id << "\n";
    }

    Tracker(const Tracker& other)
    {
        std::cout << "copied " << other.id << " to " << id << '\n';
    }

    Tracker& operator=(Tracker&& other)
    {
        other.is_moved_from = true;
        id = other.id;
        std::cout << "moved " << id << "\n";
        return *this;
    }

    Tracker& operator=(const Tracker& other)
    {
        std::cout << "copied " << other.id << " to " << id << '\n';
        return *this;
    }

    ~Tracker()
    {
        if (!is_moved_from)
        {
            std::cout << "destructed " << id << '\n';
        }
    }
};