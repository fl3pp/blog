#include <future>
#include <iostream>

template<typename TFunc>
struct AdderDecorator
{
    TFunc decoratee;
    AdderDecorator(TFunc decoratee) : decoratee{decoratee} { }

    int operator()()
    {
        int result{2};
        result += decoratee();
        result += 20;
        return result;
    }
};

int main()
{
    auto future = std::async(AdderDecorator{[]() { return 20; }});
    std::cout << future.get(); // 42
}
