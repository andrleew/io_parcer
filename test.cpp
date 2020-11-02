#include <iostream>

#include "general.h"
#include "parcer.h"

using namespace std;

int main () {
    std::cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int v, b = 1;
    int c;
    string s;
    while (ReadString(s)) {
        cout << s << '\n';
        // WriteInt(v);
        // WriteString(s);
        // WriteChar('\n');
        ++b;
    }
    return 0;
}