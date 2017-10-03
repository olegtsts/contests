#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

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
            std::vector<size_t> classes(elements_count, 0);
            do {
                if (AreClassesNamedByOrder(classes)) {
                    size_t representation = GetRepresentationByClasses(classes);
                    size_t new_index = index_representation.size();
                    if (representation_index.size() <= representation) {
                        representation_index.resize(representation + 1, 0);
                    }
                    representation_index[representation] = new_index;
                    index_representation.push_back(representation);
                }
            } while (IterateClasses(classes));
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

        std::vector<size_t> GetClassesByRepresentation(size_t representation) const {
            std::vector<size_t> classes(elements_count, 0);
            for (size_t i = elements_count; i >= 1; --i) {
                classes[static_cast<int>(i) - 1] = representation % elements_count;
                representation /= elements_count;
            }
            return classes;
        }

        EquivalentClassesState GetStateByRepresentation(size_t representation) const {
            return EquivalentClassesState(GetClassesByRepresentation(representation));
        }

        size_t GetIndex(const EquivalentClassesState& state) const {
            return representation_index[GetRepresentation(state)];
        }

        EquivalentClassesState GetState(const size_t index) const {
            return GetStateByRepresentation(index_representation[index]);
        }

        size_t GetMaxIndex() const {
            return index_representation.size();
        }
    private:
        size_t elements_count;
        std::vector<size_t> representation_index;
        std::vector<size_t> index_representation;
    };

    EquivalentClassesState(std::vector<size_t>&& input_classes)
        : classes(std::move(input_classes))
    {}

    const std::vector<size_t>& GetClasses() const {
        return classes;
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

void AddMod(long long int& var, const long long int value) {
    var += value;
    var %= MODULO;
}

void GenerateResults(const int k, const int n, const int a, std::unique_ptr<BaseResultsVisitor>&& results_visitor) {
    WWState::Indexer ww_indexer(k);
    std::vector<long long int> strings_count(ww_indexer.GetMaxIndex(), 0);
    strings_count[0] = 1;
    for (int string_length = 1; string_length <= n; ++string_length) {
        std::vector<long long int> new_strings_count(ww_indexer.GetMaxIndex(), 0);
        long long int total_strings_count = 0;
        for (size_t index = 0; index < ww_indexer.GetMaxIndex(); ++index) {
            if (strings_count[index] > 0) {
                WWState ww_state = ww_indexer.GetState(index);
                auto& classes = ww_state.last_symbols_classes.GetClasses();
                auto max_class_identificator = *std::max_element(classes.begin(), classes.end());
                for (size_t new_class = 0; new_class <= max_class_identificator + 1; ++new_class) {
                    std::vector<size_t> new_classes(classes.size());
                    for (size_t i = 0; i + 1 < new_classes.size(); ++i) {
                        new_classes[i] = classes[i + 1];
                    }
                    new_classes.back() = new_class;

                    if (new_classes[0] > 0) {
                        for (size_t i = 0; i < new_classes.size(); ++i) {
                            --new_classes[i];
                        }
                    }

                    bool is_string_ok = true;
                    IncreasingNumbersState new_shift_max_prefix;
                    for (int i = 0; i < k; ++i) {
                        // (i + 1) move last prefix size
                        size_t same_prefix_length = ww_state.shift_max_prefix.GetNumber(i);
                        if (new_class == classes[k - (i + 1)]) {
                            ++same_prefix_length;
                        }
                        if (same_prefix_length < static_cast<size_t>(i) + 1) {
                            new_shift_max_prefix.AddNumber(same_prefix_length);
                        } else {
                            is_string_ok = false;
                            break;
                        }
                    }
                    long long int coef = 1;
                    if (new_class == max_class_identificator + 1) {
                        coef = std::max(0, a - static_cast<int>(max_class_identificator) - 1);
                    }
                    if (is_string_ok && coef != 0) {
                        WWState new_ww_state(std::move(new_shift_max_prefix), EquivalentClassesState(std::move(new_classes)));
                        size_t new_index = ww_indexer.GetIndex(new_ww_state);
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
    std::unique_ptr<BaseResultsVisitor> results_visitor = std::make_unique<OutputResultsVisitor>();
    GenerateResults(3, 7, 3, std::move(results_visitor));
    return 0;
}
