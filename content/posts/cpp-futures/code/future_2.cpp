#include <future>

auto wait_for_async(std::chrono::seconds time) -> std::future<void>;
auto print_timed(std::string line) -> void;

int main()
{
    print_timed("start");               // 0s

    std::future<void> first_future = wait_for_async(std::chrono::seconds(2));
    std::future<void> second_future = wait_for_async(std::chrono::seconds(2));
    // second_future is running while we wait for first_future
    first_future.wait();
    print_timed("first completed");    // 2s
    second_future.wait();
    print_timed("second completed");   // 2s

    std::future<void> third_future = wait_for_async(std::chrono::seconds(2));
    third_future.wait();
    print_timed("third completed");    // 4s

    std::shared_future<void> ready_future{std::move(first_future)};
    std::shared_future<void> ready_future_copy = ready_future;
}

#include "helpers.cpp"