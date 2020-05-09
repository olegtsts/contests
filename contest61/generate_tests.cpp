#include <cstdlib>
#include <cassert>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <limits>


class Executor {
public:
    template <typename T>
    Executor& operator<<(const T& anything) {
        ss << anything;
        return *this;
    }
    ~Executor() {
        if (system(ss.str().c_str())) {
            std::cout << "Command '" << ss.str().c_str() << "' failed\n";
            assert(false);
        }
    }
private:
    std::stringstream ss;
};

void GenerateTests(const std::string& folder_name, const std::string& implementation_file, const std::function<void(std::ostream&)>& random_test_generator) {
    std::ios::sync_with_stdio(false);
    std::cout << "Starting to generate tests for " << folder_name << "\n";
    Executor() << "rm -rf " << folder_name;
    Executor() << "rm -f " << folder_name << ".zip";
    Executor() << "mkdir -p " << folder_name << "/input";
    Executor() << "mkdir -p " << folder_name << "/output";
    Executor() << "g++-7 " << implementation_file << " -o " << implementation_file << ".o";
    int time_sum = 0;
    int min_time = std::numeric_limits<int>::max();
    int max_time = 0;
    int tests_count = 100;
    for (int i = 0; i < tests_count; ++i) {
        std::stringstream input_file_name_ss;
        input_file_name_ss << folder_name << "/input/input" << std::setfill('0') << std::setw(2) << i << ".txt";
        std::string input_file_name = input_file_name_ss.str();
        std::ofstream out(input_file_name);
        random_test_generator(out);
        out.close();
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        Executor() << "./" << implementation_file << ".o < " << input_file_name << " > "
            << folder_name << "/output/output" << std::setfill('0') << std::setw(2) << i << ".txt";

        std::chrono::steady_clock::time_point finish_time = std::chrono::steady_clock::now();
        int current_time = std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time).count();
        time_sum += current_time;
        min_time = std::min(min_time, current_time);
        max_time = std::max(max_time, current_time);
        if ((i + 1) % 10 == 0) {
            std::cout << i + 1 << "/" << tests_count << " test cases for " << folder_name << " were generated" << std::endl;
        }
    }
    std::cout << "Stats for " << folder_name << ": min = " << min_time <<
        "ms, avg = " << static_cast<double>(time_sum) / tests_count <<
        "ms, max = " << max_time << "ms\n";
    Executor() << "rm " << implementation_file << ".o";
    std::cout << "Packing tests  into " << folder_name << ".zip...\n";
    Executor() << "zip -r " << folder_name << ".zip " << folder_name << " 1>> /dev/null 2>&1";
    std::cout << "Done " << folder_name << ".zip\n";
    Executor() << "rm -rf " << folder_name;
}

int main() {
    GenerateTests("height_of_a_binary_tree_tests", "1_new.cpp", [](std::ostream& input){
        int size_of_array = 100000;
        input << size_of_array << std::endl;
        for (int i = 0; i < size_of_array; ++i) {
            input << rand() % 100000;
            if (i + 1 < size_of_array) {
                input << " ";
            }
        }
        input << std::endl;
    });
    GenerateTests("maximum_subarray_tests", "3.cpp", [](std::ostream& input){
        input << 2 << std::endl;
        for (int j = 0; j < 2; ++j) {
            int size_of_array = 100000;
            input << size_of_array << std::endl;
            for (int i = 0; i < size_of_array; ++i) {
                input << rand() % 20000 - 10000;
                if (i + 1 < size_of_array) {
                    input << " ";
                }
            }
            input << std::endl;
        }
    });
    GenerateTests("largest_rectangle", "2_stack.cpp", [](std::ostream& input){
        int size_of_array = 100000;
        input << size_of_array << std::endl;
        for (int i = 0; i < size_of_array; ++i) {
            input << rand() % 1000000;
            if (i + 1 < size_of_array) {
                input << " ";
            }
        }
        input << std::endl;
    });

    return 0;
}
