#include <future>
#include <thread>

auto print_timed(std::string line) -> void;
auto wait_for_async(std::chrono::seconds time) -> std::future<void>;

int main()
{
    print_timed("start");                           // 0s
    auto promise = std::promise<void>{};

    auto concurrentThread = std::thread([&promise]
    {
        wait_for_async(std::chrono::seconds(2)).wait();
        promise.set_value();
    });

    auto future = promise.get_future();
    print_timed("waiting for promise to complete"); // 0s
    future.wait();
    print_timed("promise completed");               // 2s

    concurrentThread.join();
}

#include "helpers.cpp"