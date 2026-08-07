#include <future>
#include <iostream>
#include "Tracker.hpp"

int main()
{
    auto future = std::async(Tracker{});
    future.wait();
    std::cout << "------\n";
    // constructed 7
    // moved 7
    // moved 7
    // moved 7
    // operator() called on 7
    // --- end
    // destructed 7
}
