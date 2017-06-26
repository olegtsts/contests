#include <iostream>
#include <stack>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::string command;
    int number;
    std::stack<int> stack;
    std::set<int> set;
    int reorder_counter = 0;
    int element_to_remove = 1;
    for (int i = 0; i < 2 * n; ++i) {
        std::cin >> command;
        if (command == "add") {
            std::cin >> number;
            stack.push(number);
        } else {
            if (stack.size() > 0) {
                if (stack.top() == element_to_remove) {
                    stack.pop();
                } else {
                    ++reorder_counter;
                    while (stack.size() > 0) {
                        set.insert(stack.top());
                        stack.pop();
                    }
                    set.erase(element_to_remove);
                }
            } else {
                set.erase(element_to_remove);
            }
            ++element_to_remove;
        }
    }
    std::cout << reorder_counter << std::endl;
    return 0;
}
