#include <iostream>
#include <vector>

void dfs(
    std::vector<int>& work_times,
    std::vector<std::vector<int> >& graph,
    long long int& pre_time,
    long long int& post_time,
    long long int depth,
    int cur_vertex
) {
    for (auto& new_vertex: graph[cur_vertex]) {
        dfs(work_times, graph, pre_time, post_time, depth * 2, new_vertex);
    }

    pre_time += work_times[cur_vertex];
    post_time += work_times[cur_vertex] * depth;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> work_times(n);
    std::vector<std::vector<int> > graph(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> work_times[i];
    }

    for (size_t i = 0; i < n; ++i) {
        int depends_count;
        std::cin >> depends_count;
        graph[i].resize(depends_count);
        for (size_t j = 0; j < depends_count; ++j) {
            int another_node;
            std::cin >> another_node;
            graph[i][j] = another_node - 1;
        }
    }

    long long int pre_time = 0;
    long long int post_time = 0;

    dfs(work_times, graph, pre_time, post_time, 1, 0);

    std::cout << pre_time << " " << post_time << std::endl;


    return 0;
}
