#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <cstdlib>
#include <stdexcept>
#include <cstdio>
#include <unistd.h>
#include <unordered_set>
#include <vector>

class InteractiveTester {
public:
    InteractiveTester(const std::string& tested_prog, const bool output_debug)
    : tested_prog(tested_prog)
    , is_test_ok(false)
    , output_debug(output_debug)
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
            kill(pid, SIGKILL);
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

class DivisorTester : public InteractiveTester {
public:
    DivisorTester(const std::string& tested_prog,
            bool output_debug,
            int n, int x, int max_request_count)
    : InteractiveTester(tested_prog, output_debug)
    , n(n)
    , x(x)
    , remaining_values()
    , requests_count(0)
    , max_request_count(max_request_count)
    {
        for (int i = 1; i <= n; ++i) {
            remaining_values.insert(i);
        }
    }

    void pre_action() const {
        std::cerr << n << " " << x << std::endl;
        std::cout << n << std::endl;
    }

    bool respond() {
        char operation_type;
        std::cin >> operation_type;
        if (operation_type == 'A') {
            int divisor;
            std::cin >> divisor;
            if (std::cin.eof()) {
                return false;
            }
            std::cerr << "Got request A(" << divisor << ")" << std::endl;
            int response = 0;
            for (int number : remaining_values) {
                if (number % divisor == 0) {
                    ++response;
                }
            }
            std::cerr << "Given out response " << response << std::endl;
            std::cout << response << std::endl;
        } else if (operation_type == 'B') {
            int divisor;
            std::cin >> divisor;
            if (std::cin.eof()) {
                return false;
            }
            std::cerr << "Got request B(" << divisor << ")" << std::endl;
            int response = 0;
            std::vector<int> to_delete;
            for (int number : remaining_values) {
                if (number % divisor == 0) {
                    ++response;
                    if (number != x) {
                        to_delete.push_back(number);
                    }
                }
            }
            for (int number : to_delete) {
                remaining_values.erase(number);
            }
            std::cerr << std::endl;
            std::cerr << "Given out response " << response << std::endl;
            std::cout << response << std::endl;
        } else if (operation_type == 'C') {
            int answer;
            std::cin >> answer;
            if (std::cin.eof()) {
                return false;
            }
            std::cerr << "Got request C(" << answer << ")" << std::endl;
            if (answer == x) {
                mark_ok();
            }
            return false;
        } else {
            std::cerr << "Wrong request format: operation_type = " << operation_type  << "\n";
        }
        return requests_count++ < max_request_count;
        return true;
    }
private:
    int n;
    int x;
    std::unordered_set<int> remaining_values;
    int requests_count;
    int max_request_count;
};

int main (int argc, char** argv) {
    int n = 1000;
    for (int x = 1; x <= n; ++x) {
        DivisorTester("5.o", true, n, x, 10000).process_test();
    }
    DivisorTester("5.o", true, 100000, 99951, 10000).process_test();
    std::cerr << "All tests OK" << std::endl;
    return 0;
}
