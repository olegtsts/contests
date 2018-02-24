#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>

class LossKey {
public:
    LossKey() {}
    LossKey(const int minus_count, const int plus_count)
        : minus_count(minus_count)
        , plus_count(plus_count)
    {}
private:
    LossKey(const int minus_count, const int plus_count, const bool consider_plus)
        : minus_count(minus_count)
        , plus_count(plus_count)
        , consider_plus(consider_plus)
    {}
public:
    void ChooseLossKey() {
        consider_plus = plus_count < minus_count;
    }
    LossKey GetDecreasedMinus() const {
        return LossKey{minus_count - 1, plus_count, consider_plus};
    }
    LossKey GetDecreasedPlus() const {
        return LossKey{minus_count, plus_count - 1, consider_plus};
    }
    int GetKey() const {
        if (consider_plus) {
            return plus_count;
        } else {
            return minus_count;
        }
    }
    int& GetModifiableKey() {
        if (consider_plus) {
            return plus_count;
        } else {
            return minus_count;
        }
    }
    std::vector<LossKey> GetAllLessLossKeys() const {
        std::vector<LossKey> loss_keys;
        auto loss_key = *this;
        while (loss_key.GetKey() >= 0) {
            loss_keys.push_back(loss_key);
            loss_key.GetModifiableKey() -= 1;
        }
        return loss_keys;
    }
private:
    int minus_count;
    int plus_count;
    bool consider_plus;
};

class ExpressionTree {
private:
    struct MaxMinValues {
        int max_value = std::numeric_limits<int>::min();
        int min_value = std::numeric_limits<int>::max();
        bool is_combination_possible = false;

        void UpdateValues(const int new_value) {
            if (min_value > new_value) {
                min_value = new_value;
            }
            if (max_value < new_value) {
                max_value = new_value;
            }
            is_combination_possible = true;
        }
    };
    struct TreeBuilderItem {
        size_t node_index;
        int parsed_count;
    };
    struct NodeInfo {
        bool has_children = false;
        size_t left_child = 0;
        size_t right_child = 0;
        int number = 0;
    };
public:
    ExpressionTree(const std::string& expression_string) {
        size_t max_used_index = 0;
        BuildTreeRecursive(max_used_index, expression_string, 0);
    }
    TreeBuilderItem BuildTreeRecursive(size_t& max_used_index, const std::string& expression_string, const int start_index) {
        size_t current_index = max_used_index++;
        while (nodes.size() <= current_index) {
            nodes.push_back({});
        }
        if (expression_string[start_index] == '(') {
            TreeBuilderItem first_item = BuildTreeRecursive(max_used_index, expression_string, start_index + 1);
            TreeBuilderItem second_item = BuildTreeRecursive(max_used_index, expression_string, start_index + first_item.parsed_count + 2);
            nodes[current_index] = {true, first_item.node_index, second_item.node_index, 0};
            return {current_index, first_item.parsed_count + second_item.parsed_count + 3};
        } else {
            int number = 0;
            size_t string_index = start_index;
            while (expression_string[string_index] >= '0' && expression_string[string_index] <= '9') {
                number *= 10;
                number += expression_string[string_index] - '0';
                ++string_index;
            }
            nodes[current_index] = {false, 0, 0, number};
            return {current_index, static_cast<int>(string_index) - static_cast<int>(start_index)};
        }
    }

    void FindMaxMinValuesRecursive(
        std::vector<std::vector<MaxMinValues>>& vertex_loss_key_max_min_values,
        const std::vector<LossKey>& loss_keys,
        const int current_index
    ) {
        if (nodes[current_index].has_children) {
            FindMaxMinValuesRecursive(vertex_loss_key_max_min_values, loss_keys, nodes[current_index].left_child);
            FindMaxMinValuesRecursive(vertex_loss_key_max_min_values, loss_keys, nodes[current_index].right_child);

            for (auto& loss_key: loss_keys) {
                MaxMinValues& target_value = vertex_loss_key_max_min_values[current_index][loss_key.GetKey()];
                auto prev_plus_loss_key = loss_key.GetDecreasedPlus();
                if (prev_plus_loss_key.GetKey() >= 0) {
                    auto key_value = prev_plus_loss_key.GetKey();
                    for (int value = 0; value <= key_value; ++value) {
                        auto left_res = vertex_loss_key_max_min_values[nodes[current_index].left_child][value];
                        auto right_res = vertex_loss_key_max_min_values[nodes[current_index].right_child][key_value - value];
                        if (left_res.is_combination_possible && right_res.is_combination_possible) {
                            target_value.UpdateValues(left_res.min_value + right_res.min_value);
                            target_value.UpdateValues(left_res.max_value + right_res.max_value);
                        }
                    }
                }
                auto prev_minus_loss_key = loss_key.GetDecreasedMinus();
                if (prev_minus_loss_key.GetKey() >= 0) {
                    auto key_value = prev_minus_loss_key.GetKey();
                    for (int value = 0; value <= key_value; ++value) {
                        auto left_res = vertex_loss_key_max_min_values[nodes[current_index].left_child][value];
                        auto right_res = vertex_loss_key_max_min_values[nodes[current_index].right_child][key_value - value];
                        if (left_res.is_combination_possible && right_res.is_combination_possible) {
                            target_value.UpdateValues(left_res.min_value - right_res.max_value);
                            target_value.UpdateValues(left_res.max_value - right_res.min_value);
                        }
                    }
                }
            }
        } else {
            vertex_loss_key_max_min_values[current_index][0] = {nodes[current_index].number, nodes[current_index].number, true};
        }
    }

    int FindMaxResult(const LossKey& max_loss_key) {
        std::vector<LossKey> loss_keys = max_loss_key.GetAllLessLossKeys();
        std::vector<std::vector<MaxMinValues>> vertex_loss_key_max_min_values =
            std::vector<std::vector<MaxMinValues>>(nodes.size(),
                                                   std::vector<MaxMinValues>(loss_keys.size()));
        FindMaxMinValuesRecursive(vertex_loss_key_max_min_values, loss_keys, 0);
        return vertex_loss_key_max_min_values[0][max_loss_key.GetKey()].max_value;
    }
private:
    std::vector<NodeInfo> nodes;
};
int main() {
    std::string input_string;
    std::cin >> input_string;
    int plus_count, minus_count;
    std::cin >> plus_count >> minus_count;
    LossKey loss_key(minus_count, plus_count);
    loss_key.ChooseLossKey();
    ExpressionTree expression_tree(input_string);
    std::cout << expression_tree.FindMaxResult(loss_key) << std::endl;
    return 0;
}
