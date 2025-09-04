#include <iostream>
#include "Vector.hpp"

int main() {
    std::cout << "KOHLI IS THE KING." << std::endl;

    Vector<int> first(5, 1);
    Vector<int> second = {0, 1, 2};
    std::cout << second[2] << std::endl;
    second = first;
    std::cout << second[0] << std::endl;

    return 0;
}