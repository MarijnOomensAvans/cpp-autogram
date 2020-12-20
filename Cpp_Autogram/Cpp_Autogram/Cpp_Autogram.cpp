#include <iostream>
#include <random>

int main()
{
    std::random_device dev;
    std::default_random_engine dre{ dev() };
    std::uniform_int_distribution<int> dist{ 1, 6 };
    for (int i{ 0 }; i < 20; ++i) {
        std::cout << dist(dre) << "";
    }
    std::cout << "\n";
}