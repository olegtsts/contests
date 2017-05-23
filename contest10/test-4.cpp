#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stdexcept>

class InteractiveTester {
public:
    InteractiveTester(const std::string& tested_prog, const bool output_debug)
    : tested_prog(tested_prog)
    , output_debug(output_debug)
    , is_test_ok(false)
    {}

    void mark_ok() {
        is_test_ok = true;
    }

    bool process_test() {
        int prog_to_test_pipe[2];
        int test_to_prog_pipe[2];
        if (pipe(prog_to_test_pipe) < 0) {
            throw std::runtime_error("failed to open prog_to_test_pipe");
        }
        if (pipe(test_to_prog_pipe) < 0) {
            throw std::runtime_error("failed to open test_to_prog_pipe");
        }
        int pid = fork();
        if (pid > 0) {
            signal(SIGPIPE, SIG_IGN);
            if (dup2(test_to_prog_pipe[1], STDOUT_FILENO) == -1) {
                throw std::runtime_error("failed to bind pipe of test to stdout");
            }
            if (dup2(prog_to_test_pipe[0], STDIN_FILENO) == -1) {
                throw std::runtime_error("failed to bind pipe of test to stdin");
            }
            close(test_to_prog_pipe[0]);
            close(prog_to_test_pipe[1]);
            std::streambuf *old = std::cerr.rdbuf();
            if (!output_debug) {
                std::cerr.setstate(std::ios::failbit);
                std::stringstream null_stream;
                std::cerr.rdbuf(null_stream.rdbuf());
            }
            pre_action();
            while (respond()) {}
            close(test_to_prog_pipe[1]);
            close(prog_to_test_pipe[0]);
            while (waitpid(pid, NULL, WNOHANG) == 0) {}
            if (!output_debug) {
                std::cerr.rdbuf(old);
            } else {
                system("echo '=== DEBUG OUTPUT ===' 1>&2; cat debug.log >&2");
            }
        } else {
            if (dup2(test_to_prog_pipe[0], STDIN_FILENO) == -1) {
                throw std::runtime_error("failed to bind pipe of tested program to stdin");
            }
            if (dup2(prog_to_test_pipe[1], STDOUT_FILENO) == -1) {
                throw std::runtime_error("failed to bind pipe of tested program to stdout");
            }
            close(test_to_prog_pipe[1]);
            close(prog_to_test_pipe[0]);
            system((std::string("rm -f debug.log; ./") + tested_prog + std::string("  2>> debug.log")).c_str());
            close(test_to_prog_pipe[0]);
            close(prog_to_test_pipe[1]);
            exit(0);
        }
        if (is_test_ok) {
            std::cerr << "Test OK" << std::endl;
        } else {
            throw std::runtime_error("Test NOT OK");
        }
        return is_test_ok;
    }

    virtual void pre_action() const = 0;
    virtual bool respond() = 0;

    virtual ~InteractiveTester() {}
private:
    std::string tested_prog;
    bool is_test_ok;
protected:
    bool output_debug;
};

class FoodTester : public InteractiveTester {
public:
    FoodTester(const std::string& tested_prog,
            const bool output_debug,
            const int n, const std::vector<int>& chozen)
    : InteractiveTester(tested_prog, output_debug)
    , n(n)
    , k(chozen.size())
    , distances(n)
    {
        int current_closest_index = 0;
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - chozen[current_closest_index]);
            if (current_closest_index + 1 < chozen.size()
                    && distance > abs(i - chozen[current_closest_index + 1])) {
                distance = abs(i - chozen[current_closest_index + 1]);
                ++current_closest_index;
            }
            distances[i] = distance;
            if (output_debug) {
                std::cerr << i << " " << distance << std::endl;
            }
        }
    }
    void pre_action() const {
        std::cout << n << " " << k << std::endl;
    }

    bool respond() {
        int operation_type, first_index, second_index;
        std::cin >> operation_type >> first_index >> second_index;
        std::cerr << "Got command " << operation_type << " " << first_index << " " << second_index << std::endl;
        if (first_index > n || first_index <= 0) {
            std::cerr << "Wrong index" << std::endl;
            return false;
        }
        if (second_index > n || second_index <= 0) {
            std::cerr << "Wrong second index" << std::endl;
            return false;
        }
        if (operation_type == 1) {
            if (distances[first_index - 1] <= distances[second_index - 1]) {
                std::cout << "TAK" << std::endl;
                std::cerr << "TAK" << std::endl;
            } else {
                std::cout << "NIE" << std::endl;
                std::cerr << "NIE" << std::endl;
            }
            return true;
        } else if (operation_type == 2) {
            if (distances[first_index - 1] == 0 && distances[second_index - 1] == 0) {
                std::cerr << "Good response" << std::endl;
                mark_ok();
            } else {
                std::cerr << "Wrong answer" << std::endl;
            }
            return false;
        } else {
            std::cerr << "Wrong operation type" << std::endl;
            return false;
        }
    }
private:
    int n;
    int k;
    std::vector<int> distances;
};

int main (int argc, char** argv) {
    if (argc <= 1) {
        throw std::runtime_error("file name expected");
    }
    system((std::string("g++ --std=c++0x -g ") + std::string(argv[1]) + std::string(" -o tested_binary")).c_str());
//    FoodTester("tested_binary", true, 10, {1, 2, 5}).process_test();
//    exit(0);
    int n = 10;
    for (size_t i = 0; i < (1 << n); ++i) {
        std::vector<int> chozen;
        for (size_t j = 0; j < n; ++j) {
            if ((i & (1 << j)) > 0) {
                chozen.push_back(j);
            }
        }
        if (chozen.size() >= 2) {
            for (auto& el: chozen) {
                std::cerr << el << " ";
            }
            FoodTester("tested_binary", false, n, chozen).process_test();
        }
    }
    std::cerr << "All tests OK" << std::endl;
    return 0;
}
