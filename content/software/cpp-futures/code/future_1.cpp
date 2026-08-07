#include <future>

auto wait_for_async(std::chrono::seconds time) -> std::future<void>;
auto print_timed(std::string line) -> void;

int main()
{
    std::future<void> first_future = wait_for_async(std::chrono::seconds(2));

    print_timed("start");   // 0s: start
    first_future.wait();
    print_timed("end");     // 2s: end
}

#include "helpers.cpp"