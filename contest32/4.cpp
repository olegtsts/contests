#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class WordTree {
private:
    struct Child {
        bool is_there_anything = false;
        size_t index = 0;
    };
    struct WordNode {
        char letter;
        std::vector<Child> children;
        size_t children_count;
        bool is_finalized;

        WordNode()
            : letter('a')
            , children('z' - 'a' + 1, {false, 0})
            , children_count(0)
            , is_finalized(false)
        {
        }

        WordNode(const char letter)
            : letter(letter)
            , children('z' - 'a' + 1, {false, 0})
            , children_count(0)
            , is_finalized(false)
        {
        }

        bool IsThereChild(const char letter) {
            return children[letter - 'a'].is_there_anything;
        }

        size_t GetChildIndex(const char letter) {
            return children[letter - 'a'].index;
        }

        void AddChild(const char letter, const size_t index) {
            int letter_index = letter - 'a';
            auto& child = children[letter_index];
            if (!child.is_there_anything) {
                child.is_there_anything = true;
                ++children_count;
                child.index = index;
            }
        }
    };
public:
    WordTree()
        : nodes(300001)
        , max_index(1)
    {
    }

    int InsertWordAndGetMinSteps(const std::string& word) {
        WordNode* current_node = &nodes[0];
        int last_index_with_single_child = -1;
        int total_score = 0;
        for (size_t i = 0; i < word.size(); ++i) {
            char symbol = word[i];
            if (current_node->IsThereChild(symbol)) {
                if (current_node->children_count == 1 && !current_node->is_finalized) {
                    if (last_index_with_single_child == -1) {
                        last_index_with_single_child = i;
                    }
                } else {
                    last_index_with_single_child = -1;
                }
                current_node = &nodes[current_node->GetChildIndex(symbol)];
            } else {
                if (last_index_with_single_child >= 0 && current_node->children_count == 0) {
                    total_score += std::min(1 - (static_cast<int>(i) - last_index_with_single_child) + (last_index_with_single_child == 0 ? 1 : 0), 0);
                }
                WordNode* next_node = &nodes[max_index];
                current_node->AddChild(symbol, max_index);
                ++max_index;
                current_node = next_node;
                last_index_with_single_child = -1;
            }
        }
        if (last_index_with_single_child >= 0 && current_node->children_count == 0) {
            total_score += std::min(1 - (static_cast<int>(word.size()) - last_index_with_single_child) + (last_index_with_single_child == 0 ? 1 : 0), 0);
        }
        current_node->is_finalized = true;
        return static_cast<int>(word.size()) + total_score;
    }
private:
    std::vector<WordNode> nodes;
    size_t max_index;
};

int main() {
    std::string word;
    std::string text((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
    int total_score = 0;
    WordTree tree;
    for (size_t i = 0; i < text.size(); ++i) {
        char symbol = text[i];
        if (symbol >= 'a' && symbol <= 'z') {
            word.push_back(symbol);
        } else {
            total_score += 1;
        }
        if (word.size() > 0 && (i + 1 == text.size() || !(text[i + 1] >= 'a' && text[i + 1] <= 'z'))) {
            int word_score = tree.InsertWordAndGetMinSteps(word);
            total_score += word_score;
//            std::cout << word << " " << word_score << std::endl;
            word = std::string();
        }
    }
    std::cout << total_score << std::endl;
    return 0;
}
