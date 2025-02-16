#include <future>
#include <iostream>

int main()
{
    auto task = std::packaged_task<int()>{[]
    {
        return 42;
    }};

    task();

    auto future = task.get_future();
    std::cout << future.get() << std::endl; // 42
}
