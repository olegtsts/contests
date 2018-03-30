#include <iostream>
#include <string>

enum class Response {CORRECT, TOO_SMALL, TOO_BIG};

Response GetResponse(const long long int number) {
    std::cout << number << std::endl << std::flush;
    std::string response;
    std::cin >> response;
    std::cerr << "Response to " << number << " is " << response << std::endl;
    if (response == "CORRECT") {
        return Response::CORRECT;
    } else if (response == "TOO_SMALL") {
        return Response::TOO_SMALL;
    } else {
        return Response::TOO_BIG;
    }
}

void DoTest() {
    long long int lower,upper;
    std::cin >> lower >> upper;
    int max_attempts;
    std::cin >> max_attempts;
    while (upper - lower >= 2) {
        long long int middle = (upper + lower) / 2;
        Response middle_response = GetResponse(middle);
        if (middle_response == Response::CORRECT) {
            return;
        } else if (middle_response == Response::TOO_SMALL) {
            lower = middle;
        } else {
            upper = middle;
        }
    }
    if (GetResponse(lower) == Response::CORRECT) {
        return;
    }
    GetResponse(upper);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        DoTest();
    }
    return 0;
}
