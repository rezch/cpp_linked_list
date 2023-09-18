#include <iostream>
#include "list.h"
#include <string>
#include <stack>


int main() {

    list l = list<std::string>("hello");

    l.append("world");

    for (int i = 0; i < l.size(); i++) {
        std::cout << l[i] << std::endl;
    }

    std::stack<int> st;
    st.push(14);
    st.push(124);
    list l2 = list<std::stack<int>>(st);
    std::cout << l2[0].top() << std::endl;

    return 0;
}
