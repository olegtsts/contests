#include <string>
#include <vector>
#include <iostream>

class DisjointSet{
public:
    std::vector<int> parent;

    DisjointSet(int n):
        parent(n)
    {
        for(int i=0; i<n; i++) {
            parent[i] = i;
        }
    }

    void join(int a, int b) { parent[find(b)] = find(a); }

    int find(int a){ return a == parent[a] ? a : parent[a] = find(parent[a]); }

    bool check(int a, int b) { return find(a) == find(b); }
};

int GetIndex(char symbol) {
    if (symbol >= '0' && symbol <= '9') {
        return symbol - '0';
    }
    if (symbol >= 'a' && symbol <= 'z') {
        return symbol - 'a' + 1 + ('9' - '0');
    }
    if (symbol >= 'A' && symbol <= 'Z') {
        return symbol - 'A' + 2 + ('z' - 'a') + ('9' - '0');
    }
    if (symbol == '_') {
        return 'Z' - 'A' + 'z' - 'a' + '9' - '0' + 3;
    }
    return -1;
}

class LettersClassifier {
public:
    LettersClassifier()
        : disjoined_set(GetIndex('_') + 1)
    {
        for (char s = 'a'; s <= 'z'; ++s) {
            disjoined_set.join(GetIndex(s), GetIndex(s - 'a' + 'A'));
        }
        disjoined_set.join(GetIndex('0'), GetIndex('O'));
        disjoined_set.join(GetIndex('1'), GetIndex('l'));
        disjoined_set.join(GetIndex('l'), GetIndex('I'));
    }

    bool AreLettersSame(const char first_char, const char second_char) {
        return disjoined_set.check(GetIndex(first_char), GetIndex(second_char));
    }
private:
    DisjointSet disjoined_set;
};


bool AreLoginsSame(
    LettersClassifier& letters_classifier,
    const std::string& first_string,
    const std::string& second_string
) {
    if (first_string.size() != second_string.size()) {
        return false;
    }
    for (size_t i = 0; i < first_string.size(); ++i) {
        if (!letters_classifier.AreLettersSame(first_string[i], second_string[i])) {
            return false;
        }
    }
    return true;
}


int main() {
    std::ios::sync_with_stdio(false);
    LettersClassifier letters_classifier;
    std::vector<char> indices_mapping;
    std::string new_login;
    std::cin >> new_login;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string try_login;
        std::cin >> try_login;
        if (AreLoginsSame(letters_classifier, new_login, try_login)) {
            std::cout << "No\n";
            return 0;
        }
    }
    std::cout << "Yes\n";
    return 0;
}
