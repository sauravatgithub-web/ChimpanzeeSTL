template <typename Iter>
class ReverseIterator {
public:
    using iterator_type     = Iter;
    using iterator_category = typename std::iterator_traits<Iter>::iterator_category;
    using value_type        = typename std::iterator_traits<Iter>::value_type;
    using difference_type   = typename std::iterator_traits<Iter>::difference_type;
    using pointer           = typename std::iterator_traits<Iter>::pointer;
    using reference         = typename std::iterator_traits<Iter>::reference;

    ReverseIterator() : current() {}
    explicit ReverseIterator(Iter it) : current(it) {}

    template <typename Other>
    ReverseIterator(const ReverseIterator<Other>& other) : current(other.base()) {}

    Iter base() const { return current; }

    reference operator*() const {
        Iter tmp = current;
        return *--tmp; 
    }
    pointer operator->() const { return std::addressof(operator*()); }


    ReverseIterator& operator++() { --current; return *this; }
    ReverseIterator operator++(int) { ReverseIterator tmp = *this; --current; return tmp; }
    ReverseIterator& operator--() { ++current; return *this; }
    ReverseIterator operator--(int) { ReverseIterator tmp = *this; ++current; return tmp; }

    ReverseIterator operator+(difference_type n) const { return ReverseIterator(current - n); }
    ReverseIterator operator-(difference_type n) const { return ReverseIterator(current + n); }
    difference_type operator-(const ReverseIterator& other) const { return other.current - current; }

    ReverseIterator& operator+=(difference_type n) { current -= n; return *this; }
    ReverseIterator& operator-=(difference_type n) { current += n; return *this; }

    reference operator[](difference_type n) const { return *(*this + n); }

    friend bool operator==(const ReverseIterator& a, const ReverseIterator& b) { return a.current == b.current; }
    friend bool operator!=(const ReverseIterator& a, const ReverseIterator& b) { return a.current != b.current; }
    friend bool operator< (const ReverseIterator& a, const ReverseIterator& b) { return b.current < a.current; }
    friend bool operator> (const ReverseIterator& a, const ReverseIterator& b) { return b.current > a.current; }
    friend bool operator<=(const ReverseIterator& a, const ReverseIterator& b) { return b.current <= a.current; }
    friend bool operator>=(const ReverseIterator& a, const ReverseIterator& b) { return b.current >= a.current; }

private:
    Iter current;
};