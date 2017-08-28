#include <iostream>
#include <vector>
#include <utility>

int GetPowerOfTwo(const long long int number) {
    for (int i = 1; i < 64; ++i) {
        if (number < (1ll << i)) {
            return i - 1;
        }
    }
    throw std::logic_error("GetPowerOfTwo failed");
}

void Update(std::vector<long long int>& power_numbers, long long int number) {
    while (number > 0) {
        int power_of_two = GetPowerOfTwo(number);
        if (power_numbers[power_of_two] == -1) {
            power_numbers[power_of_two] = number;
            break;
        } else {
            number ^= power_numbers[power_of_two];
        }
    }
}

long long int Reduce(std::vector<long long int>& power_numbers, long long int number) {
    for (int i = 63; i >= 0; --i) {
        if (power_numbers[i] >= 0 && number > (number ^ power_numbers[i])) {
            number = number ^ power_numbers[i];
        }
    }
    return number;
}

void dfs(
    std::vector<std::vector<std::pair<int, long long int>>>& graph,
    std::vector<long long int>& power_numbers,
    std::vector<long long int>& first_distances,
    const long long int cur_distance,
    const int vertex
) {
    if (first_distances[vertex] >= 0) {
        Update(power_numbers, first_distances[vertex] ^ cur_distance);
    } else {
        first_distances[vertex] = cur_distance;
        for (auto& neighbour_and_distance: graph[vertex]) {
            auto neighbour = neighbour_and_distance.first;
            auto new_distance = neighbour_and_distance.second;
            dfs(graph, power_numbers, first_distances, cur_distance ^ new_distance, neighbour);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, long long int>>> graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        long long int w;
        std::cin >> x >> y;
        --x;
        --y;
        std::cin  >> w;
        graph[x].push_back(std::make_pair(y, w));
        graph[y].push_back(std::make_pair(x, w));
    }
    std::vector<long long int> power_numbers(64, -1);
    std::vector<long long int> first_distances(n, -1);
    dfs(graph, power_numbers, first_distances, 0, 0);
    std::cout << Reduce(power_numbers, first_distances[n - 1]) << std::endl;
    return 0;
}
