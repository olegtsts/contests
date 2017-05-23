#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void depth_fast_search(
    std::unordered_map<long long int, std::vector<long long int> >& neighbours,
    std::unordered_set<long long int>& people,
    long long int start,
    long long int& edges_count,
    long long int& people_count
) {
    if (people.count(start)) {
        people.erase(start);
        if (neighbours.count(start)) {
            for (auto& neighbour: neighbours[start]) {
                ++edges_count;
                depth_fast_search(neighbours, people, neighbour, edges_count, people_count);
            }
        }
        ++people_count;
    }
}

int main () {
    long long int n,m;
    std::cin >> n >> m;

    std::unordered_map<long long int, std::vector<long long int> > neighbours;
    std::unordered_set<long long int> people;
    for (size_t i = 0; i < m; ++i) {
        long long int first, second;
        std::cin >> first >> second;
        --first;
        --second;
        neighbours[first].push_back(second);
        neighbours[second].push_back(first);
        people.insert(first);
        people.insert(second);
    }

    while (people.size() > 0) {
        long long int start = *(people.begin());
        long long int edges_count = 0;
        long long int people_count = 0;
        depth_fast_search(neighbours, people, start, edges_count, people_count);
        if (edges_count != people_count * (people_count - 1)) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }

    std::cout << "YES" << std::endl;
    return 0;
}
