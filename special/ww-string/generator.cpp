#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <climits>
#include <fstream>
#include <cassert>
#include <ctime>

const long long int MODULO = 1000000007;

class IncreasingNumbersState {
public:
    class Indexer {
    public:
        Indexer(const size_t input_max_number)
        : max_number(input_max_number)
        {}

        size_t GetMaxIndex() const {
            size_t result = 1;
            for (size_t i = 1; i <= max_number; ++i) {
                result *= i;
            }
            return result;
        }

        size_t GetIndex(const IncreasingNumbersState& state) const {
            size_t result_index = 0;
            for (size_t i = max_number; i >= 1; --i) {
                result_index *= i;
                result_index += state.GetNumber(static_cast<int>(i) - 1);
            }
            return result_index;
        }

        IncreasingNumbersState GetState(size_t index) const {
            IncreasingNumbersState state;
            for (size_t i = 0; i < max_number; ++i) {
                state.AddNumber(index % (i + 1));
                index /= (i + 1);
            }
            return state;
        }
    private:
        size_t max_number;
    };

    size_t GetNumber(const size_t index) const {
        return numbers.at(index);
    }

    void AddNumber(const size_t number) {
        numbers.push_back(number);
    }

    friend std::ostream& operator<<(std::ostream& out, const IncreasingNumbersState& state) {
        out << "(";
        for (size_t i = 0; i < state.numbers.size(); ++i) {
            out << state.numbers[i];
            if (i + 1 < state.numbers.size()) {
                out << " ";
            }
        }
        out << ")";
        return out;
    }
private:
    std::vector<int> numbers;
};


class EquivalentClassesState {
public:
    class Indexer {
    public:
        Indexer(const size_t input_elements_count)
            : elements_count(input_elements_count)
        {
            BuildRepresentationsState();
        }

        bool CheckIncreasingClasses(const std::vector<size_t>& classes) const {
            if (classes.size() == 0) {
                return true;
            }
            if (classes[0] > 0) {
                return false;
            }
            size_t current_classes = 0;
            size_t prev_element = LLONG_MAX;
            for (auto& el: classes) {
                if (prev_element == el) {
                    return false;
                }
                if (el > current_classes + 1) {
                    return false;
                } else if (el > current_classes) {
                    current_classes = el;
                }
                prev_element = el;
            }
            for (size_t k = 1; k <= elements_count; ++k) {
                for (size_t i = 0; i + 2 * k < classes.size(); ++i) {
                    bool are_strings_same = true;
                    for (size_t j = 0; j < k; ++j) {
                        if (classes[i + j] != classes[i + k + j]) {
                            are_strings_same = false;
                            break;
                        }
                    }
                    if (are_strings_same) {
                        return false;
                    }
                }
            }
            return true;
        }

        std::vector<size_t> NormalizeClasses(const std::vector<size_t>& classes) const {
            std::vector<size_t> normalized_classes(classes.size(), 0);
            std::vector<size_t> increasing_classes;
            std::vector<bool> used_classes(elements_count, false);
            for (auto& class_number: classes) {
                if (!used_classes[class_number]) {
                    increasing_classes.push_back(class_number);
                    used_classes[class_number] = true;
                }
            }
            std::vector<size_t> reverse_increasing_classes(elements_count + 1, 0);
            for (size_t i = 0; i < increasing_classes.size(); ++i) {
                reverse_increasing_classes[increasing_classes[i]] = i;
            }
            for (size_t i = 0; i < classes.size(); ++i) {
                normalized_classes[i] = reverse_increasing_classes[classes[i]];
            }
            return normalized_classes;
        }

        bool AreClassesNamedByOrder(const std::vector<size_t>& classes) const {
            size_t last_used = 0;
            if (classes[0] != 0) {
                return false;
            }
            for (size_t i = 1; i < classes.size(); ++i) {
                if (classes[i] >= last_used + 2) {
                    return false;
                }
                if (classes[i] >= last_used) {
                    last_used = classes[i];
                }
            }
            return true;
        }

        bool IterateClasses(std::vector<size_t>& classes) const {
            for (size_t i = 0; i < classes.size(); ++i) {
                classes[i] += 1;
                if (classes[i] == elements_count) {
                    classes[i] = 0;
                } else {
                    return true;
                }
            }
            return false;
        }

        void BuildRepresentationsState() {
            size_representation_index.resize(elements_count + 1);
            for (size_t postfix_length = 0; postfix_length <= elements_count; ++postfix_length) {
                std::vector<size_t> classes(postfix_length, 0);
                do {
                    if (CheckIncreasingClasses(classes)) {
                        size_t representation = GetRepresentationByClasses(classes);
                        while (size_representation_index[postfix_length].size() < representation + 1) {
                            size_representation_index[postfix_length].push_back(LLONG_MAX);
                        }
                        if (size_representation_index[postfix_length][representation] == LLONG_MAX) {
                            size_t new_index = index_representation_size.size();
                            size_representation_index[postfix_length][representation] = new_index;
                            index_representation_size.push_back(std::make_pair(postfix_length, representation));
                        }
                    }
                } while (IterateClasses(classes));
            }
        }

        size_t GetRepresentationByClasses(const std::vector<size_t>& classes) const {
            size_t result = 0;
            for (auto& num: classes) {
                result *= elements_count;
                result += num;
            }
            return result;
        }

        size_t GetRepresentation(const EquivalentClassesState& state) const {
            return GetRepresentationByClasses(state.GetClasses());
        }

        std::vector<size_t> GetClassesByRepresentation(size_t postfix_length, size_t representation) const {
            std::vector<size_t> classes(postfix_length, 0);
            for (size_t i = postfix_length; i >= 1; --i) {
                classes[static_cast<int>(i) - 1] = representation % elements_count;
                representation /= elements_count;
            }
            return classes;
        }

        EquivalentClassesState GetStateByPostfixLengthAndRepresentation(const size_t postfix_length, const size_t representation) const {
            return EquivalentClassesState(GetClassesByRepresentation(postfix_length, representation));
        }

        size_t GetIndex(const EquivalentClassesState& state) const {
            size_t size_of_state = state.GetClasses().size();
            size_t representation = GetRepresentation(NormalizeClasses(state.GetClasses()));
            assert(size_of_state < size_representation_index.size());
            assert(representation < size_representation_index[size_of_state].size());
            return size_representation_index[size_of_state][representation];
        }

        EquivalentClassesState GetState(const size_t index) const {
            auto postfix_length_and_representation = index_representation_size[index];
            return GetStateByPostfixLengthAndRepresentation(
                postfix_length_and_representation.first,
                postfix_length_and_representation.second);
        }

        size_t GetMaxIndex() const {
            return index_representation_size.size();
        }
    private:
        size_t elements_count;
        std::vector<std::vector<size_t>> size_representation_index;
        std::vector<std::pair<size_t, size_t>> index_representation_size;
    };

    EquivalentClassesState(std::vector<size_t>&& input_classes)
        : classes(std::move(input_classes))
    {}

    const std::vector<size_t>& GetClasses() const {
        return classes;
    }
    friend std::ostream& operator<<(std::ostream& out, const EquivalentClassesState& state) {
        out << "[";
        for (size_t i = 0; i < state.classes.size(); ++i) {
            out << state.classes[i];
            if (i + 1 < state.classes.size()) {
                out << " ";
            }
        }
        out << "]";
        return out;
    }
private:
    std::vector<size_t> classes;
};


class WWState {
public:
    WWState(
        IncreasingNumbersState&& input_shift_max_prefix,
        EquivalentClassesState&& input_last_symbols_classes
    )
        : shift_max_prefix(std::move(input_shift_max_prefix))
        , last_symbols_classes(std::move(input_last_symbols_classes))
    {}

    class Indexer {
    public:
        Indexer(const size_t k)
            : shift_max_prefix_indexer(k)
            , last_symbols_classes_indexer(k)
        {}

        size_t GetMaxIndex() const {
            return shift_max_prefix_indexer.GetMaxIndex() * last_symbols_classes_indexer.GetMaxIndex();
        }

        size_t GetIndex(const WWState& state) const {
            size_t index = 0;
            index += shift_max_prefix_indexer.GetIndex(state.shift_max_prefix);
            index *= last_symbols_classes_indexer.GetMaxIndex();
            index += last_symbols_classes_indexer.GetIndex(state.last_symbols_classes);
            return index;
        }

        WWState GetState(size_t index) const {
            EquivalentClassesState last_symbols_classes = last_symbols_classes_indexer.GetState(
                index % last_symbols_classes_indexer.GetMaxIndex());
            index /= last_symbols_classes_indexer.GetMaxIndex();
            IncreasingNumbersState shift_max_prefix = shift_max_prefix_indexer.GetState(index);
            return WWState(std::move(shift_max_prefix), std::move(last_symbols_classes));
        }

    private:
        IncreasingNumbersState::Indexer shift_max_prefix_indexer;
        EquivalentClassesState::Indexer last_symbols_classes_indexer;
    };

    friend std::ostream& operator<<(std::ostream& out, const WWState& state) {
        return out << "<" << state.shift_max_prefix << ", " << state.last_symbols_classes << ">";
    }
public:
    IncreasingNumbersState shift_max_prefix;
    EquivalentClassesState last_symbols_classes;
};

class BaseResultsVisitor {
public:
    struct Result {
        int k;
        int n;
        int a;
        long long int word_count;
    };

    virtual void AddResult(const Result& result) = 0;

    virtual ~BaseResultsVisitor() {
    }
};

class OutputResultsVisitor : public BaseResultsVisitor {
public:
    void AddResult(const BaseResultsVisitor::Result& result) {
        std::cout << result.k << " " << result.n << " " << result.a << " " << result.word_count << std::endl;
    }
};

class CodeGenerationVisitor : public BaseResultsVisitor {
public:
    void AddResult(const BaseResultsVisitor::Result& result) {
        results.push_back(result);
    }

    friend std::ostream& operator<<(std::ostream& out, const CodeGenerationVisitor& code_generation_visitor) {
        out << "#include<iostream>\n\n";
        out << "int main() {\n";
        out << "int k,n,a;\n";
        out << "\tstd::cin >> k >> n >> a;\n";
        out << "long long int result = 0;\n\t";
        for (size_t i = 0; i < code_generation_visitor.results.size(); ++i) {
            auto& res = code_generation_visitor.results[i];
            out << "if (k == " << res.k << " && n == " << res.n << " && a == " << res.a << ") {\n";
            out << "\t\tresult = " << res.word_count << ";\n";
            out << "\t}";
            if (i + 1 < code_generation_visitor.results.size()) {
                out << " else ";
            } else {
                out << "\n";
            }
        }
        out << "\tstd::cout << result << std::endl;\n";
        out << "\treturn 0;\n";
        out << "}";
        return out;
    }
private:
    std::vector<BaseResultsVisitor::Result> results;
};

void AddMod(long long int& var, const long long int value) {
    var += value;
    var %= MODULO;
}

void GenerateResults(WWState::Indexer& ww_indexer, const int k, const int n, const int a, std::unique_ptr<BaseResultsVisitor>&& results_visitor) {
    std::vector<long long int> strings_count(ww_indexer.GetMaxIndex(), 0);
    strings_count[0] = 1;
    for (int string_length = 1; string_length <= n; ++string_length) {
        std::vector<long long int> new_strings_count(ww_indexer.GetMaxIndex(), 0);
        long long int total_strings_count = 0;
        std::cout << std::time(0) << " :: length = " << string_length << std::endl;
        for (size_t index = 0; index < ww_indexer.GetMaxIndex(); ++index) {
            assert(index < strings_count.size());
            if (strings_count[index] > 0) {
                WWState ww_state = ww_indexer.GetState(index);
                std::vector<size_t> classes = ww_state.last_symbols_classes.GetClasses();
                size_t next_class_identificator;
                if (classes.size() == 0) {
                    next_class_identificator = 0;
                } else {
                    next_class_identificator = *std::max_element(classes.begin(), classes.end()) + 1;
                }
                for (size_t new_class = 0; new_class <= next_class_identificator; ++new_class) {
                    std::vector<size_t> new_classes(classes.size());
                    if (classes.size() == static_cast<size_t>(k)) {
                        for (size_t i = 0; i + 1 < new_classes.size(); ++i) {
                            assert(i < new_classes.size());
                            assert(i + 1 < classes.size());
                            new_classes[i] = classes[i + 1];
                        }
                        new_classes.back() = new_class;
                    } else {
                        for (size_t i = 0; i < new_classes.size(); ++i) {
                            assert(i < new_classes.size());
                            assert(i < classes.size());
                            new_classes[i] = classes[i];
                        }
                        new_classes.push_back(new_class);
                    }

                    bool is_string_ok = true;
                    IncreasingNumbersState new_shift_max_prefix;
                    size_t i = 0;
                    for (; i < classes.size(); ++i) {
                        size_t same_prefix_length = ww_state.shift_max_prefix.GetNumber(i);
                        assert(static_cast<int>(classes.size()) - static_cast<int>(i + 1) >= 0);
                        assert(static_cast<int>(classes.size()) - static_cast<int>(i + 1) < static_cast<int>(classes.size()));
                        if (new_class == classes[static_cast<int>(classes.size()) - static_cast<int>(i + 1)]) {
                            ++same_prefix_length;
                        } else {
                            same_prefix_length = 0;
                        }
                        if (same_prefix_length < static_cast<size_t>(i) + 1) {
                            new_shift_max_prefix.AddNumber(same_prefix_length);
                        } else {
                            new_shift_max_prefix.AddNumber(0);
                            is_string_ok = false;
                            break;
                        }
                    }
                    while (i++ < static_cast<size_t>(k)) {
                        new_shift_max_prefix.AddNumber(0);
                    }
                    long long int coef = 1;
                    if (new_class == next_class_identificator) {
                        coef = std::max(0, a - static_cast<int>(next_class_identificator));
                    }
                    if (is_string_ok && coef != 0) {
                        WWState new_ww_state(std::move(new_shift_max_prefix), EquivalentClassesState(std::move(new_classes)));
                        size_t new_index = ww_indexer.GetIndex(new_ww_state);
                        assert(new_index < new_strings_count.size());
                        assert(index < strings_count.size());
                        AddMod(new_strings_count[new_index], strings_count[index] * coef);
                        AddMod(total_strings_count, strings_count[index] * coef);
                    }
                }
            }
        }
        results_visitor->AddResult({k, string_length, a, total_strings_count});
        strings_count = std::move(new_strings_count);
    }
}

int main() {
    std::unique_ptr<BaseResultsVisitor> results_visitor = std::make_unique<CodeGenerationVisitor>();
    for (int k = 1; k <= 9; ++k) {
        WWState::Indexer ww_indexer(k);
        std::cout << "Done building indexer\n";
        for (int a = 1; a <= 26; ++a) {
            GenerateResults(ww_indexer, k, 100, a, std::move(results_visitor));
            std::cout << std::time(0) << " :: Done generating for k = " << k << ", a = " << a << std::endl;
        }
    }
    std::ofstream out("generated-programm.cpp");
    out << *static_cast<CodeGenerationVisitor*>(results_visitor.get());
    return 0;
}
