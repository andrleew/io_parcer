#pragma once

#include<iostream>

#include <iostream>
inline void ok () {std::cout << "ok\n";}

template <typename T>
inline T TenMult(T t) {
    return (t << 1) + (t << 3);
}

template<typename T>
bool ReadInt(T& value) {
    value = 0;
    register int c = getchar_unlocked();
    for (; c != EOF && (c < '0' || c > '9') && c != '-'; c = getchar_unlocked());
    if (c == EOF) return false;
    bool neg = (c == '-');
    if (neg) c = getchar_unlocked();
    for (; c != EOF && c >= '0' && c <= '9'; c = getchar_unlocked()) {
        value = TenMult(value) + (c - '0');
    }
    if (neg) value = -value;
    return true;
}

inline bool IsSpace(char c) {
    return c == '\n' || c == ' ';
}

bool ReadString(std::string& str) {
    str.clear();
    register auto c = getchar_unlocked();
    while (std::isspace(c)) c = getchar_unlocked();
    while (c != EOF && !std::isspace(c)) {
        str.push_back(c);
        c = getchar_unlocked();
    }
    return c != EOF;
}

inline
void WriteChar(char c) { putchar_unlocked(c); }

void WriteString(const std::string& str) {
    register const char* data = str.data();
    for (size_t i = 0; i < str.size(); ++i) putchar_unlocked(*(data++));
}

template<typename T>
void WriteInt(const T& value) {
    // WriteString(std::to_string(value));
    if (value == 0) {
        putchar_unlocked('0');
        return;
    }
    register int pow = 1;
    register T v = value;
    if (v < 0) {
        putchar_unlocked('-');
        v = -v;
    }
    register int count = 0;
    while ((value / pow) > 10) {
        pow *= 10;
        ++count;
    }
    while (count--) {
        putchar_unlocked(v / pow % 10);
        pow /= 10;
    }
}
