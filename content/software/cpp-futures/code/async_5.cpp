#include <future>
#include <iostream>



int main()
{
    auto first_future = std::async([]
    {
        return 22;
    });

    auto second_future = std::async([first_future = std::move(first_future)] mutable
    {
        return first_future.get() + 20;
    });

    std::cout << second_future.get(); // 42
}
