#include <future>

auto wait_for_async(std::chrono::seconds time) -> std::future<void>;
auto print_timed(std::string line) -> void;

int main()
{
    print_timed("start");            // 0s

    std::future<void> const async = std::async(std::launch::async, []
    {
        wait_for_async(std::chrono::seconds(2)).get();
    });

    print_timed("started waiting");  // 0s
    async.wait();
    print_timed("end");              // 2s
}

#include "helpers.cpp"