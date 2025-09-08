#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.hpp"

int main() {
    std::cout << "KOHLI IS THE KING." << std::endl;

    Vector<int> first = {3, 2, 1, 4};
    
    std::reverse(first.begin(), first.end());
    for(auto it = first.begin(); it != first.end(); it++) {
        std::cout << *it << std::endl;
    }

    return 0;
}