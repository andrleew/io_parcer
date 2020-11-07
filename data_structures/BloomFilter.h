#pragma once

#include <bitset>

// вероятностная структура данных на проверку наличия элемента

template<class T, std::size_t Size = 1024>
class TBloomFilter {
public:
    inline
    void Add (const T& value) {
        Filter.set(Hash(value) % Size);
    }

    inline
    bool Test (const T& value) const {
        return Filter.test(Hash(value) % Size);
    }

    inline constexpr size_t size() {return Size;}

private:
    std::bitset<Size> Filter;
    std::hash<T> Hash;
};