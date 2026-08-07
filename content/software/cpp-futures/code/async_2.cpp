#include <future>
#include <iostream>

struct AddX
{
    int first;
    AddX(int first) : first(first) {}

    int operator()(int second) const
    {
        return first + second;
    }
};

int main()
{
    auto adder = AddX{20};
    std::cout << std::async(adder, 22).get() << std::endl;
}
