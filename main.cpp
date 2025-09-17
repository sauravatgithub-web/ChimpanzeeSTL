#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.hpp"

int main() {
    std::cout << "KOHLI IS THE KING." << std::endl;

    Vector<int> first = {3, 2, 1, 4, 6};
    Vector<int> second = {3, 2, 1, 4, 6};

    std::cout << (first <= second) << std::endl;
    
    // std::sort(first.begin(), first.end());
    for(Vector<int>::Iterator it = first.begin(); it != first.end(); it++) {
        std::cout << *it << std::endl;
    }

    return 0;
}