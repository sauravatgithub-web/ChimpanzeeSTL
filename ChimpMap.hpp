# pragma once
#include <string>
#include "Vector.hpp"

typedef std::string Key;

template <typename T>
class ChimpMap {
private:
    struct Node {
        Node* children[26];
        bool isEndOfWord;
        T value;
    
        Node() : isEndOfWord(false) {
            for(int i = 0; i < 26; ++i) {
                children[i] = nullptr;
            }
        }

        bool empty() {
            bool yes = true;
            for(int i = 0; i < 26; i++) {
                if(children[i]) {
                    yes = false;
                    break;
                }
            }

            return yes;
        }
    };

    Node* root;
    int keyCount;
public:
    // CONSTRUCTORS

    // 1. Default Constructor
    ChimpMap() { 
        root = new Node(); 
        keyCount = 0;
    }

    // 2. Copy Constructor
    ChimpMap(ChimpMap<T>& other) {  
        root = copyNode(other.node);             
        keyCount = other.keyCount;
    }

    Node* copyNode(Node* root) {
        if(!root) return nullptr;
        Node* newNode = new Node();
        newNode->isEndOfWord = root->isEndOfWord;
        newNode->value = root->value;
        for(int i = 0; i < 26; i++) {
            newNode->children[i] = copyNode(root->children[i]);
        }
        return newNode;
    }

    // 3. Brace-enclosed initialized list Constructor
    ChimpMap(std::initializer_list<std::pair<const Key, T>> init) : ChimpMap() {
        for(const auto& [key, value] : init) {
            (*this)[key] = value;
        }
        keyCount = init.size();
    }

    // 4. Move Constructor
    ChimpMap(ChimpMap&& other) noexcept {
        root = other.root;
        keyCount = other.keyCount;

        other.root = nullptr;
        other.keyCount = 0;
    }


    // ITERATOR
    struct Iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::pair<Key, T>;
        using pointer           = value_type*;
        using reference         = value_type&;

        Vector<std::tuple<Node*, int, Key>> ahead;
        Vector<std::tuple<Node*, int, Key>> back;
        value_type current;


        Iterator(Node* root, int value = 0) {
            if(root) push(root, "");
            if(value == 0) ++(*this);
            else pushAll();
        }

        reference operator*() { return current; }
        pointer operator->() { return this; }

        Iterator& operator++() { 
            while(!ahead.empty()) {
                auto [node, i, prefix] = ahead.back();
                ahead.pop_back();

                if(node->isEndOfWord) {
                    back.push_back({node, i, prefix});
                    current = {prefix, node->value};
                    push(node, prefix);
                    return *this;
                }

                push(node, prefix);
            }
            
            current = {};
            return *this;
        }

        Iterator& operator--() {
            if(!back.empty()) {
                if(current != std::pair<Key, T>{}) {
                    auto next = back.back();
                    back.pop_back();
                    ahead.push_back(next);
                }

                auto [node, i, prefix] = back.back();
                current = {prefix, node->value};
                push(node, prefix);
                return *this;
            }

            current = {};
            return *this;
        }

        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

    private:
        void push(Node* node, std::string prefix) {
            for(int i = 25; i >= 0; i--) {
                if(node->children[i]) {
                    ahead.push_back({node->children[i], i, prefix + char('a' + i)});
                }
            }
        }

        Iterator& pushAll() {
            while(!ahead.empty()) {
                auto [node, i, prefix] = ahead.back();
                ahead.pop_back();

                if(node->isEndOfWord) {
                    back.push_back({node, i, prefix});
                    current = {prefix, node->value};
                    push(node, prefix);
                }

                push(node, prefix);
            }

            current = {};
            return *this;
        }
    };

    // Const Iterator
    struct ConstIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::pair<Key, T>;
        using pointer           = value_type*;
        using reference         = value_type&;

        Vector<std::tuple<Node*, int, Key>> ahead;
        Vector<std::tuple<Node*, int, Key>> back;
        value_type current;


        ConstIterator(Node* root, int value = 0) {
            if(root) push(root, "");
            if(value == 0) ++(*this);
            else pushAll();
        }

        reference operator*() { return current; }
        pointer operator->() { return this; }

        ConstIterator& operator++() { 
            while(!ahead.empty()) {
                auto [node, i, prefix] = ahead.back();
                ahead.pop_back();

                if(node->isEndOfWord) {
                    back.push_back({node, i, prefix});
                    current = {prefix, node->value};
                    push(node, prefix);
                    return *this;
                }

                push(node, prefix);
            }
            
            current = {};
            return *this;
        }

        ConstIterator& operator--() {
            if(!back.empty()) {
                if(current != std::pair<Key, T>{}) {
                    auto next = back.back();
                    back.pop_back();
                    ahead.push_back(next);
                }

                auto [node, i, prefix] = back.back();
                current = {prefix, node->value};
                push(node, prefix);
                return *this;
            }

            current = {};
            return *this;
        }

        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

    private:
        void push(Node* node, std::string prefix) {
            for(int i = 25; i >= 0; i--) {
                if(node->children[i]) {
                    ahead.push_back({node->children[i], i, prefix + char('a' + i)});
                }
            }
        }

        ConstIterator& pushAll() {
            while(!ahead.empty()) {
                auto [node, i, prefix] = ahead.back();
                ahead.pop_back();

                if(node->isEndOfWord) {
                    back.push_back({node, i, prefix});
                    current = {prefix, node->value};
                    push(node, prefix);
                }

                push(node, prefix);
            }

            current = {};
            return *this;
        }
    };

    Iterator begin()  { return Iterator(root); }                         
    Iterator end()    { return Iterator(root, 1); }
    ConstIterator begin()  const { return ConstIterator(root); }             
    ConstIterator end()    const { return ConstIterator(root, 1); }
    ConstIterator cbegin() const { return ConstIterator(root); }         
    ConstIterator cend()   const { return ConstIterator(root, 1 ); }


    // MEMBER FUNCTIONS
    size_t length() const { return keyCount;      }
    bool empty()    const { return keyCount == 0; }

    void insert(const Key& key, const T& value);
    T& at(const Key& key);
    bool count(const Key& key);
    void erase(const Key& key);
    void clear() { 
        clear(root); 
        root = new Node();
        keyCount = 0;
    }

    template <class... Args>
    void emplace(const Key& key, Args&&... args);

    // OVERLOADED OPERATORS
    T& operator[](const Key& key);
    const T& operator[](const Key& key) const;

    ChimpMap<T>& operator=(const ChimpMap<T>& other);  /* Copy Assignment Operator */
    ChimpMap<T>& operator=(std::initializer_list<std::pair<const Key, T>> init);

    ChimpMap<T>& operator=(ChimpMap&& other) noexcept; /* Move Assignment Operator */

    
    ~ChimpMap() { clear(root); }
    void clear(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; i++) clear(node->children[i]);
        delete node;
    }
};    

template <typename T>
void ChimpMap<T>::insert(const Key& key, const T& value) {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }
    if(node->isEndOfWord) return;

    node->isEndOfWord = true;
    node->value = value;
    keyCount++;
}

template <typename T>
T& ChimpMap<T>::at(const Key& key) {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }

    if(node->isEndOfWord == false) {
        std::cerr << "Key " << key << " not available." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return node->value;
}

template <typename T>
bool ChimpMap<T>::count(const Key& key) {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }

    return node->isEndOfWord;
}

template <typename T>
void ChimpMap<T>::erase(const Key& key) {
    if(!root) return;
    
    Node* node = root;
    Vector<std::pair<Node*, char>> path; 

    for(char ch : key) {
        if(!node->children[ch - 'a']) return; 

        path.push_back({node, ch});
        node = node->children[ch - 'a'];
    }

    if(!node->isEndOfWord) return;

    node->isEndOfWord = false;

    for(int i = (int)path.length() - 1; i >= 0; i--) {
        Node* parent = path[i].first;
        char ch = path[i].second;
        Node* child = parent->children[ch - 'a'];

        if(child->isEndOfWord || !child->empty()) break; 

        delete child;
        parent->children[ch - 'a'] = nullptr;
    }

    keyCount--;
}

template <typename T>
template <class... Args>
void ChimpMap<T>::emplace(const Key& key, Args&&... args) {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }
    if(node->isEndOfWord == false) keyCount++;

    new (&node->value) T(std::forward<Args>(args)...); 
    node->isEndOfWord = true;  
}

template <typename T>
T& ChimpMap<T>::operator[](const Key& key) {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }

    if(node->isEndOfWord == false) keyCount++;

    node->isEndOfWord = true;
    return node->value;
}

template <typename T>
const T& ChimpMap<T>::operator[](const Key& key) const {
    Node* node = root;
    for(char ch : key) {
        int index = ch - 'a';
        if(!node->children[index]) {
            node->children[index] = new Node();
        }
        node = node->children[index];
    }

    if(node->isEndOfWord == false) {
        std::cerr << "Key not found" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return node->value;
}

template <typename T>
ChimpMap<T>& ChimpMap<T>::operator=(const ChimpMap<T>& other) {
    if(this != &other) {
        root = other.root;
        keyCount = other.keyCount;
    }
    
    return *this;
}

template <typename T>
ChimpMap<T>& ChimpMap<T>::operator=(std::initializer_list<std::pair<const Key, T>> init) {
    clear();
    for(const auto& [key, value] : init) {
        (*this)[key] = value;
    }
    this->keyCount = init.size();
    return *this;
}

template <typename T>
ChimpMap<T>& ChimpMap<T>::operator=(ChimpMap&& other) noexcept {
    if(this != &other) {
        root = other.root;
        keyCount = other.keyCount;

        other.root = nullptr;
        other.keyCount = 0;
    }
    
    return *this;
}