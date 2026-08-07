#include <future>
#include <iostream>

int main()
{
    auto sum = std::packaged_task<int(int, int)>{[](int first, int second)
    {
        return first + second;
    }};

    sum(20, 22);

    auto future = sum.get_future();
    std::cout << future.get() << std::endl; // 42
}
