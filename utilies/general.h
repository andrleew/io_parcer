#pragma once

#include <iterator>
#define in :

class range {
public:
    explicit range(int64_t _end)
    : start_v(0)
    , end_v(_end) {}

    explicit range(int64_t _start, int64_t _end)
    : start_v(_start)
    , end_v(_end) {}

    class TIterator : public std::iterator<std::input_iterator_tag, int64_t, int64_t, const int64_t* , int64_t> {
    private:
        int64_t start, end;
    public:
        explicit TIterator(const int64_t _start, const int64_t _end)
        : start(_start)
        , end(_end) {}

        TIterator& operator++() {
            start += (end > start ? 1 : -1);
            return *this;
        }

        TIterator operator++(int) {
            auto ret = *this;
            ++(*this);
            return ret;
        }

        inline
        bool operator==(const TIterator& other) {
            return start == other.start && end == other.end;
        }

        inline
        bool operator!=(const TIterator& other) {
            return start != other.start || end != other.end;
        }

        reference operator*() const {return start;}
    };

    TIterator begin() { return TIterator(start_v, end_v); }
    TIterator end() { return TIterator(end_v, end_v); }

private:
    int64_t start_v, end_v;
};