#include <iostream>
#include "list.h"


int main() {
    int a[] = { 1, 2, 333, 4, 5, 6 };

    list l = list(a, sizeof(a) / sizeof(a[0]));

    l = l.reverse();

    for (int i = 0; i < l.size(); i++) {
        std::cout << l[i] << ' ';
    }

    std::cout << std::endl;

    return 0;
}
