#include <future>
#include <exception>

auto print_timed(std::string line) -> void;
auto wait_for_async(std::chrono::seconds time) -> std::future<void>;

int main()
{
    print_timed("start");                           // 0s
    auto promise = std::promise<int>{};

    auto concurrentThread = std::thread([&promise]
    {
        try
        {
            throw std::logic_error{"an exception occurred"};
        }
        catch (...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    try
    {
        promise.get_future().get();
    }
    catch(...)
    {
        print_timed("exception caught");             // 0s
    }

    concurrentThread.join();
}

#include "helpers.cpp"