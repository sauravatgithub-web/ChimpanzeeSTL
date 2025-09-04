# pragma once
#include <cstddef> 

template <class T>
class Vector {
private:
    T* array;
    size_t size;
    size_t capacity;

public:
    // CONSTRUCTORS
    
    // 1. Default Constructor
    Vector() : size(0), capacity(0) {}

    // 2. Constructor
    Vector(int n, T elem = 0) : size(n), capacity(n) {
        array = new T[capacity];
        for(int i = 0; i < (int)size; i++) {
            array[i] = elem;
        }
    }

    // 3. Copy Constructor
    Vector(Vector<T>& other) {               
        size = other.size;
        capacity = other.capacity;

        array = new T[capacity];
        for(int i = 0; i < (int)size; i++) {
            array[i] = other[i];
        }
    }

    // 4. Brace-enclosed initialized list Constructor
    Vector(std::initializer_list<T> init) {
        size = init.size();
        capacity = size;
        array = new T[capacity];
        std::copy(init.begin(), init.end(), array);
    }

    // 5. Move Constructor
    Vector(Vector&& other) noexcept {
        size = other.size;
        capacity = other.capacity;
        array = other.array;

        other.size = 0;
        other.capacity = 0;
        other.array = nullptr;
    }

    size_t length() const { return size;      }
    bool empty()    const { return size == 0; }


    void push_back(const T& elem);
    void pop_back();
    T at(int index);

    // OVELOADED OPERATORS
    T& operator[](int index);
    const T& operator[](int index) const;

    Vector<T>& operator=(const Vector<T>& other);  /* Copy Assignment Operator */
    Vector<T>& operator=(Vector&& other) noexcept; /* Move Assignment Operator */

    // Destructors
    ~Vector() {
        for(int i = 0; i < (int)size; i++){
            array[i].~T();
        }
        delete[] array;
        size = 0;
        capacity = 0;
    }
};

template <class T>
void Vector<T>::push_back(const T& elem) {
    if(size == capacity) {
        capacity = (capacity == 0 ? 1 : capacity * 2);
        T* newArray = new T[capacity];

        for(size_t i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    }

    array[size++] = elem;
}

template <class T>
void Vector<T>::pop_back() {
    if(size == 0) return;

    array[size-1].~T();
    size--;
}

template <class T>
T Vector<T>::at(int index) {
    return array[index];
}

template <class T>
T& Vector<T>::operator[](int index) {
    if(index >= size) {
        std::cerr << "Index " << index << " out of bound." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    return array[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const {
    if(index >= size) {
        std::cerr << "Index " << index << " out of bound." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    return array[index];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if(this != &other) {
        delete[] array;

        size = other.size;
        capacity = other.capacity;
        array = new T[capacity];

        for(int i = 0; i < (int)size; i++) {
            array[i] = other[i];
        }
    }
    
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if(this != &other) {
        delete[] array;

        size = other.size;
        capacity = other.capacity;
        array = other.array;

        other.size = 0;
        other.capacity = 0;
        other.array = nullptr;
    }
    
    return *this;
}