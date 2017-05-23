#include <iostream>
#include <vector>
#include <set>
#include <queue>


int main () {
    int n,m;
    std::cin >> n >> m;
    std::vector<long long int> distances(n * m * 4, 10);
    std::vector<bool> is_blocked(n * m, false);
    long long int start_r;
    long long int start_c;
    long long int finish_r;
    long long int finish_c;

    std::priority_queue<std::pair<int, long long int> > not_visited;
    std::vector<bool> is_visited(n * m, false);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            char ch;
            std::cin >> ch;
            if (ch == '.') {
            } else if (ch == '*') {
                is_blocked[j * n + i] = true;
            } else if (ch == 'S') {
                start_r = i;
                start_c = j;
                for (size_t k = 0; k < 4; ++k) {
                    distances[(j * n + i) * 4 + k] = 0;
                }
            } else if (ch == 'T') {
                finish_r = i;
                finish_c = j;
            }
            if (!is_blocked[j * n + i]) {
                for (int k = 0; k < 4; ++k) {
                    long long int index = (j * n + i) * 4 + k;
                    not_visited.push(std::make_pair(-distances[index], index));
                }
            }
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        distances[(start_c * n + start_r) * 4 + i] = 0;
    }

//    for (auto& pair: not_visited) {
//        auto& vertex = pair.second;
//        auto& distance = pair.first;
//        auto rotation = vertex % 4;
//        auto vertex_r = (vertex / 4) % n;
//        auto vertex_c = vertex / 4 / n;
//
//        std::cout << "distance = " << distance << " (" << vertex_r << "," << vertex_c << "," << rotation << ")" << std::endl;
//    }


    while (!not_visited.empty()) {
//        auto& pair = *(not_visited.begin());
//        auto& vertex = pair.second;
//        auto& distance = pair.first;
//        auto not_visited_copy = not_visited;
//        while (not_visited_copy.size() > 0) {
//            auto el = not_visited_copy.top();
//            not_visited_copy.pop();
//            auto rotation = el.second % 4;
//
//            auto vertex_r = (el.second / 4) % n;
//            auto vertex_c = el.second / 4 / n;
//
//            std::cout << el.first << " (" << vertex_r << "," << vertex_c << "," << rotation << ")" << std::endl;
//        }

        auto top = not_visited.top();
        not_visited.pop();
//        std::cout << "Size = " << not_visited.size() << std::endl;
        long long int vertex = top.second;
        int distance = -top.first;
        auto rotation = vertex % 4;
        auto vertex_r = (vertex / 4) % n;
        auto vertex_c = vertex / 4 / n;

//        std::cout << "distance = " << distance << ", stored " << distances[vertex] << " " << "Chozen (" << vertex_r << "," << vertex_c << "," << rotation << ")" << std::endl;
        if (distance > distances[vertex]) {
            continue;
        }
//        std::cout << "distance = " << distance << " " << "Chozen (" << vertex_r << "," << vertex_c << "," << rotation << ")" << std::endl;

        std::vector<std::pair<int, long long int> > distances_and_new_vertices;
        if (vertex_r + 1 < n) {
            distances_and_new_vertices.push_back(std::make_pair(1, (vertex_c * n + vertex_r + 1) * 4 + 1));
        }
        if (vertex_r >= 1) {
            distances_and_new_vertices.push_back(std::make_pair(3, (vertex_c * n + vertex_r - 1) * 4 + 3));
        }
        if (vertex_c + 1 < m) {
            distances_and_new_vertices.push_back(std::make_pair(0, ((vertex_c + 1) * n + vertex_r) * 4 + 0));
        }
        if (vertex_c >= 1) {
            distances_and_new_vertices.push_back(std::make_pair(2, ((vertex_c - 1) * n + vertex_r) * 4 + 2));
        }
        for (auto& move_pair: distances_and_new_vertices) {
            auto& new_rotation = move_pair.first;
            long long int new_index = move_pair.second;
            auto new_vertex_r = (new_index / 4) % n;
            auto new_vertex_c = new_index / 4 / n;
            int old_distance = distances[new_index];
            if (!is_visited[new_index] && !is_blocked[new_vertex_c * n + new_vertex_r]) {
                int addon_points = 0;
                if (new_rotation != rotation) {
                    addon_points = 1;
                }
                int new_distance = addon_points + distances[vertex];
                if (old_distance > new_distance) {
                    distances[new_index] = new_distance;
//                    not_visited.erase(std::make_pair(old_distance, new_index));
                    not_visited.push(std::make_pair(-new_distance, new_index));
//                    std::cout << "Pushed distance = " << new_distance << " (" << new_vertex_r << "," << new_vertex_c << "," << new_rotation << ")" << std::endl;
                }
            }
        }
        is_visited[vertex] = true;
//        not_visited.erase(pair);

//        std::cout << "-------------------------\n";
//        for (size_t i = 0; i < n; ++i) {
//            for (size_t j = 0; j < m; ++j) {
//                std::cout << "(";
//                for (size_t k = 0; k < 4; ++k) {
//                    std::cout << distances[(j * n + i) * 4 + k];
//                    if (k < 3) {
//                        std::cout << ",";
//                    }
//                }
//                std::cout << ")";
//                 if (j + 1 < m) {
//                    std::cout << " ";
//                }
//            }
//            std::cout << std::endl;
//        }
    }

    bool can_reach = false;
    for (size_t k = 0; k < 4; ++k) {
//        std::cout << distances[(finish_c * n + finish_r) * 4 + k] << std::endl;
        if (distances[(finish_c * n + finish_r) * 4 + k] <= 2) {
            can_reach = true;
        }
    }
    if (can_reach) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
