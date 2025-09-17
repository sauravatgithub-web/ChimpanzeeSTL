# pragma once
#include <iterator>
#include <cstddef> 
#include <memory>
#include <utility>
#include <algorithm>
#include "ReverseIterator.hpp"

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

    // ITERATOR
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(pointer ptr) : v_ptr(ptr) {}

        reference operator*() const { return *v_ptr; }
        pointer operator->() { return v_ptr; }

        Iterator& operator++() { v_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { v_ptr--; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        Iterator operator+(difference_type n) const { return Iterator(v_ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(v_ptr - n); }
        difference_type operator-(const Iterator& other) const { return v_ptr - other.v_ptr; }

        Iterator operator+=(difference_type n) const { v_ptr += n; return *this; }
        Iterator operator-=(difference_type n) const { v_ptr -= n; return *this; }

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.v_ptr == b.v_ptr; };
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.v_ptr != b.v_ptr; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.v_ptr < b.v_ptr; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.v_ptr > b.v_ptr; };
        friend bool operator<=(const Iterator& a, const Iterator& b) { return a.v_ptr <= b.v_ptr; };
        friend bool operator>=(const Iterator& a, const Iterator& b) { return a.v_ptr >= b.v_ptr; };

    private:
        pointer v_ptr;
    };

    struct ConstIterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        ConstIterator(pointer ptr) : v_ptr(ptr) {}

        reference operator*() const { return *v_ptr; }
        pointer operator->() const { return v_ptr; }

        ConstIterator& operator++() { v_ptr++; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
        ConstIterator& operator--() { v_ptr--; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

        ConstIterator operator+(difference_type n) const { return ConstIterator(v_ptr + n); }
        ConstIterator operator-(difference_type n) const { return ConstIterator(v_ptr - n); }
        difference_type operator-(const ConstIterator& other) const { return v_ptr - other.v_ptr; }

        ConstIterator operator+=(difference_type n) { v_ptr += n; return *this; }
        ConstIterator operator-=(difference_type n) { v_ptr -= n; return *this; }

        friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.v_ptr == b.v_ptr; };
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.v_ptr != b.v_ptr; };
        friend bool operator< (const ConstIterator& a, const ConstIterator& b) { return a.v_ptr < b.v_ptr; };
        friend bool operator> (const ConstIterator& a, const ConstIterator& b) { return a.v_ptr > b.v_ptr; };
        friend bool operator<=(const ConstIterator& a, const ConstIterator& b) { return a.v_ptr <= b.v_ptr; };
        friend bool operator>=(const ConstIterator& a, const ConstIterator& b) { return a.v_ptr >= b.v_ptr; };

    private:
        pointer v_ptr;
    };

    Iterator begin()  { return Iterator(array); }                              // for non const object
    Iterator end()    { return Iterator(array + size); }
    ConstIterator begin() const { return ConstIterator(array); }               // for const object
    ConstIterator end()   const { return ConstIterator(array + size); }
    ConstIterator cbegin() const { return ConstIterator(array); }              // const iterators on any
    ConstIterator cend()   const { return ConstIterator(array + size); }

    ReverseIterator<Iterator> rbegin() { return ReverseIterator<Iterator>(end()); }
    ReverseIterator<Iterator> rend() { return ReverseIterator<Iterator>(begin()); }
    ReverseIterator<ConstIterator> rbegin() const { return ReverseIterator<ConstIterator>(end()); }
    ReverseIterator<ConstIterator> rend() const { return ReverseIterator<ConstIterator>(begin()); }
    ReverseIterator<ConstIterator> rcbegin() const { return ReverseIterator<ConstIterator>(end()); }
    ReverseIterator<ConstIterator> rcend() const { return ReverseIterator<ConstIterator>(begin()); }

    // MEMEBER FUNCTIONS

    size_t length() const { return size;      }
    bool empty()    const { return size == 0; }
    T front()       const { return array[0];  }
    T back()    const { return array[size-1]; }
    T* data()             { return array;     }
    const T* data() const { return array;     }

    void push_back(const T& elem);
    void pop_back();
    void clear();
    T at(int index);
    void resize(int n, const T& value = 0);
    void reserve(int n);
    void shrink_to_fit();

    void insert(const Iterator& iter, const T& val);
    void insert(const Iterator& iter, int count, const T& val);
    void erase(const Iterator& iter);
    void erase(const Iterator& first, const Iterator& last);
    void assign(int count, const T& val);
    void assign(std::initializer_list<T> ilist);

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);

    template <class... Args>
    void emplace_back(Args&&... args);

    // OVELOADED OPERATORS
    T& operator[](int index);
    const T& operator[](int index) const;

    Vector<T>& operator=(const Vector<T>& other);  /* Copy Assignment Operator */
    Vector<T>& operator=(Vector&& other) noexcept; /* Move Assignment Operator */

    template <class U> friend bool operator==(const Vector<U>& lhs, const Vector<U>& rhs);
    template <class U> friend bool operator!=(const Vector<U>& lhs, const Vector<U>& rhs);
    template <class U> friend bool operator<(const Vector<U>& lhs, const Vector<U>& rhs);
    template <class U> friend bool operator<=(const Vector<U>& lhs, const Vector<U>& rhs);
    template <class U> friend bool operator>(const Vector<U>& lhs, const Vector<U>& rhs);
    template <class U> friend bool operator>=(const Vector<U>& lhs, const Vector<U>& rhs);

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
void Vector<T>::clear() {
    for(int i = 0; i < (int)size; i++) {
        array[i].~T();
    }
    size = 0;
}

template <class T>
T Vector<T>::at(int index) {
    return array[index];
}

template <class T>
void Vector<T>::resize(int n, const T& value) {
    if(n < (int)capacity) {
        if(n < (int)size) {
            while(size > n) {
                array[size-1].~T();
                size--;
            }
        }
        else {
            while(size < n) {
                array[size] = value;
                size++;
            }
        }
    }
    else {
        capacity = n;
        T* newArray = new T[capacity];

        for(size_t i = 0; i < capacity; i++) {
            if(i < size) newArray[i] = array[i];
            else newArray[i] = value;
        }

        delete[] array;
        array = newArray;
    }
}

template <class T>
void Vector<T>::reserve(int n) {
    if(n < (int)capacity) {
        return;
    }
    else {
        capacity = n;
        T* newArray = new T[capacity];

        for(size_t i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    }
}

template <class T>
void Vector<T>::shrink_to_fit() {
    if(capacity == size) return;
    capacity = size;
    T* newArray = new T[capacity];

    for(size_t i = 0; i < size; i++) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
}

template <class T>
void Vector<T>::insert(const Iterator& iter, const T& val) {
    insert(iter, 1, val);
}

template <class T>
void Vector<T>::insert(const Iterator& iter, int count, const T& val) {
    if(iter - begin() >= size) {
        std::cerr << "Index out of range." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if(capacity >= size + count) {
        Iterator rit = end() + count - 1;
        while((int)(rit - iter) >= count) {
            *rit = *(rit - count);
            rit--;
        }
        for(int i = 1; i <= count; i++) {
            *rit = val;
            rit--;
        }
    }
    else {
        capacity *= 2;
        T* newArray = new T[capacity];

        Iterator it = begin();
        while(it != iter) {
            *(newArray + (int)(it - begin())) = *it;
            it++;
        }
        for(int i = 0; i < count; i++) {
            *(newArray + i + (int)(iter - begin())) = val;
        }
        while(it != end()) {
            *(newArray + count + (int)(it - begin())) = *it;
            it++;
        }

        delete[] array;
        array = newArray;
    }
    size += count;
}

template <class T>
void Vector<T>::erase(const Iterator& iter) {
    Iterator it = begin();
    while(it != iter) it++;
    if(it >= end()) {
        std::cerr << "Unknown memory access" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    while(it + 1 != end()) {
        *(it) = *(it + 1);
        it++;
    }
    size--;
}

template <class T>
void Vector<T>::erase(const Iterator& first, const Iterator& last) {
    Iterator it = begin();
    while(it != first) it++;
    if(it >= end()) {
        std::cerr << "Unknown memory access" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    Iterator next_it = it + 1;
    while(next_it != end() && next_it != last) next_it++;
    while(next_it != end()) {
        *(it) = *(next_it);
        it++;
        next_it++;
    }
    size = it - begin();
}

template <class T>
void Vector<T>::assign(int count, const T& val) {
    if(capacity < count) {
        capacity = count;
        T* newArray = new T[capacity];
        delete[] array;
        array = newArray;
    }

    for(int i = 0; i < count; i++) {
        array[i] = val;
    }
    size = count;
}

template <class T>
template <class InputIterator>
void Vector<T>::assign(InputIterator first, InputIterator last) {
    int count = last - first;
    if(capacity < count) {
        capacity = count;
        T* newArray = new T[capacity];
        delete[] array;
        array = newArray;
    }

    Iterator it = begin();
    for(int i = 0; i < count; i++) {
        *(it + i) = *first;
        first++;
    }
    size = count;
}

template <class T>
void Vector<T>::assign(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
}

template <class T>
template <class... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if(size == capacity) {
        capacity = (capacity == 0 ? 1 : capacity * 2);
        T* newArray = new T[capacity];

        for(size_t i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    }

    new (array + size) T(std::forward<Args>(args)...);
    size++;
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

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    return lhs.size == rhs.size && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}  

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}  

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}   

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}   

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return (rhs < lhs);
}   

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}   