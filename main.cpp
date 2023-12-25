#include <iostream>
#include <string>
#include <stack>

#include "list.h"


int main() {

    int v[] = {1, 2, 3};

    list l = list<int>(v, sizeof(v) / sizeof(int));
    l.append(4);


    std::cout << l.size() << std::endl;

    return 0;
}
