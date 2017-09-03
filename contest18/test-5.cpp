#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <cstdlib>
#include <stdexcept>
#include <cstdio>
#include <unistd.h>

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

class XorTester : public InteractiveTester {
public:
    XorTester(const std::string& tested_prog,
            const bool output_debug,
            const int n, const long long int x, const long long int y,
            const int first_index, const int second_index)
    : InteractiveTester(tested_prog, output_debug)
    , n(n)
    , x(x)
    , y(y)
    , first_index(first_index)
    , second_index(second_index)
    {
    }
    void pre_action() const {
        std::cerr << n << " " << x << " " << y << std::endl;
        std::cout << n << " " << x << " " << y << std::endl;
    }

    bool respond() {
        char operation_type;
        std::cin >> operation_type;
        if (operation_type == '?') {
            int size;
            std::cin >> size;
            long long int response = 0;
            for (int i = 0; i < size; ++i) {
                int index;
                std::cin >> index;
                if (index == first_index || index == second_index) {
                    response ^= y;
                } else {
                    response ^= x;
                }
            }
            std::cerr << "Given out response " << response << std::endl;
            std::cout << response << std::endl;
            return true;
        } else if (operation_type == '!') {
            int res_first_index;
            int res_second_index;
            std::cin >> res_first_index >> res_second_index;
            if (res_first_index == first_index && res_second_index == second_index) {
                mark_ok();
            }
            std::cerr << "Here answer given " << res_first_index << " " << res_second_index << "\n";
            return false;
        } else {
            std::cerr << "Wrong request format\n";
        }
        return true;
    }
private:
    int n;
    int x;
    int y;
    int first_index;
    int second_index;
};

int main (int argc, char** argv) {
    int n = 4;
    long long int x = 2;
    long long int y = 1;
    int first_index = 1;
    int second_index = 3;
    XorTester("5.o", true, n, x, y, first_index, second_index).process_test();
    std::cerr << "All tests OK" << std::endl;
    return 0;
}
