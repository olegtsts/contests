#include <iostream>

int main() {
    long long int n,k;
    std::cin >> n >> k;
    long long int l,r;
    l = 0;
    r = n;
    std::string response;
    while (r - l > 3) {
        long long int l_mid = (r - l) / 3 + l;
        long long int r_mid = (r - l) * 2 / 3 + l;
        std::cout << 1 << " " << l_mid + 1 << " " << r_mid + 1 << std::endl;
//        fflush(stdout);
        std::cin >> response;
        if (response == "TAK") {
            r = r_mid;
        } else if (response == "NIE") {
            l = l_mid;
        } else {
            throw 1;
        }
    }
    long long int first_found;
    if (r - l == 3) {
        std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//        fflush(stdout);
        std::cin >> response;
        if (response == "TAK") {
            first_found = l;
        } else {
            std::cout << 1 << " " << l + 2 + 1 << " " << l + 1 + 1 << std::endl;
//            fflush(stdout);
            if (response == "TAK") {
                first_found = l + 2;
            } else {
                first_found = l + 1;
            }
        }
    } else if (r - l == 2) {
        std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//        fflush(stdout);
        std::cin >> response;
        if (response == "NIE") {
            first_found = l + 1;
        } else {
            first_found = l;
        }
    } else if (r - l == 1) {
        first_found = l;
    }
    l = first_found;
    r = n;
    bool still_nie = true;
    while (r - l > 3) {
        long long int l_mid = (r - l) / 3 + l;
        long long int r_mid = (r - l) * 2 / 3 + l;
        std::cout << 1 << " " << r_mid + 1 << " " << l_mid + 1 << std::endl;
//        fflush(stdout);
        std::cin >> response;
        if (response == "TAK") {
            l = l_mid;
            still_nie = false;
        } else if (response == "NIE" && still_nie) {
            r = l_mid;
        } else if (response == "NIE" && !still_nie) {
            r = r_mid;
        } else {
            throw 1;
        }
    }
    if (!still_nie) {
        long long int second_found;
        if (r - l == 3) {
            std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//            fflush(stdout);
            std::cin >> response;
            if (response == "TAK") {
                second_found = l;
            } else {
                std::cout << 1 << " " << l + 2 + 1 << " " << l + 1 + 1 << std::endl;
//                fflush(stdout);
                if (response == "TAK") {
                    second_found = l + 2;
                } else {
                    second_found = l + 1;
                }
            }
        } else if (r - l == 2) {
            std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//            fflush(stdout);
            std::cin >> response;
            if (response == "NIE") {
                second_found = l + 1;
            } else {
                second_found = l;
            }
        } else if (r - l == 1) {
            second_found = l;
        }
        std::cout << 2 << " " << first_found + 1 << " " << second_found + 1 << std::endl;
//        fflush(stdout);
        return 0;
    } else {
        long long int second_found = -1;
        for (long long int i = l + 1; i < r; ++i) {
            std::cout << 1 << " " << i + 1 << " " << first_found + 1 << std::endl;
//            fflush(stdout);
            std::cin >> response;
            if (response == "TAK") {
                second_found = i;
                break;
            }
        }
        if (second_found >= 0) {
            std::cout << 2 << " " << first_found + 1 << " " << second_found + 1 << std::endl;
//            fflush(stdout);
            return 0;
        } else {
            l = 0;
            r = first_found;
            while (r - l > 3) {
                long long int l_mid = (r - l) / 3 + l;
                long long int r_mid = (r - l) * 2 / 3 + l;
                std::cout << 1 << " " << l_mid + 1 << " " << r_mid + 1 << std::endl;
//                fflush(stdout);
                std::cin >> response;
                if (response == "TAK") {
                    r = r_mid;
                } else if (response == "NIE") {
                    l = l_mid;
                } else {
                    throw 1;
                }
            }
            long long int second_found;
            if (r - l == 3) {
                std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//                fflush(stdout);
                std::cin >> response;
                if (response == "TAK") {
                    second_found = l;
                } else {
                    std::cout << 1 << " " << l + 2 + 1 << " " << l + 1 + 1 << std::endl;
//                    fflush(stdout);
                    if (response == "TAK") {
                        second_found = l + 2;
                    } else {
                        second_found = l + 1;
                    }
                }
            } else if (r - l == 2) {
                std::cout << 1 << " " << l + 1 << " " << l + 1 + 1 << std::endl;
//                fflush(stdout);
                std::cin >> response;
                if (response == "NIE") {
                    second_found = l + 1;
                } else {
                    second_found = l;
                }
            } else if (r - l == 1) {
                second_found = l;
            }
            std::cout << 2 << " " << first_found + 1 << " " << second_found + 1 << std::endl;
//            fflush(stdout);
            return 0;
        }
    }
    return 0;
}
