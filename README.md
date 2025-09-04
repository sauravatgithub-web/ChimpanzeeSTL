# 🦧 ChimpanzeeSTL  

A **college-level reimplementation of the C++ Standard Template Library (STL)** for learning data structures, templates, and object-oriented programming.  

> Why "Chimpanzee"? Because sometimes learning feels like monkey business 🐒 — but we’re evolving toward mastery.

---

## ✨ Features  

- 📦 **Vector** — dynamic array with push/pop, indexing, resizing  
- 🔄 Copy & Move Semantics (Rule of Five)  
- ⚡ Efficient memory management (`new[]`, `delete[]`)  
- 🧪 Test programs for each container  

Planned:  
- 📝 List  
- 🌳 Map/Set (tree-based)  
- 🏗 Stack, Queue  

---

## 📂 Project Structure  
```
ChimpanzeeSTL/
    │── include/ # Header files (Vector.hpp, etc.)
    │── src/ # Implementation files if separated
    │── tests/ # Example programs testing containers
    │── README.md # This file
```

---

## 🚀 Getting Started  

Clone the repository:  
```bash
git clone https://github.com/your-username/ChimpanzeeSTL.git
cd ChimpanzeeSTL
```

Compile and run a test
```bash
g++ tests/vector_test.cpp -I include -o vector_test
./vector_test
```

## 🧑‍💻 Example Usage
```cpp
#include "Vector.hpp"
#include <iostream>

int main() {
    Vector<int> v = {1, 2, 3};

    v.push_back(4);
    v.pop_back();

    for (size_t i = 0; i < v.length(); i++) {
        std::cout << v[i] << " ";
    }
}
```

## 📘 Learning Goals
This project is built to:
- Understand how STL containers are designed under the hood
- Practice templates, dynamic memory, and const-correctness
- Explore copy vs move semantics (Rule of 5)
- Gain insight into complexity analysis of operations

## 🤝 Contributing
Contributions are welcome! Feel free to fork the repo, create a branch, and submit a PR.