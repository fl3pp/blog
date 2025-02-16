#include <future>
#include <iostream>
#include "Tracker.hpp"

int main()
{
    auto future = std::async([]
    {
        Tracker tracker{};
        return tracker;
    });

    auto tracker = future.get();
    std::cout << "tracker id: " << tracker.id << '\n';
}
