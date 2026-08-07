#pragma once

#include <iostream>
#include <future>
#include <chrono>

auto wait_for_async(std::chrono::seconds time) -> std::future<void>
{
    return std::async(std::launch::async, [time]
    {
        std::this_thread::sleep_for(time);
    });
}

auto const now = std::chrono::system_clock::now(); 

auto print_timed(std::string line) -> void
{
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - now).count() << "s: " << line << std::endl;
} 
