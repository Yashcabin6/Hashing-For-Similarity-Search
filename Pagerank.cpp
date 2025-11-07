#include <iostream>
#include <vector>

int main() {
    const double ALP = 0.85; 
    std::vector<std::vector<int>> links;
    int p, q;
    while (std::cin >> p >> q) {
        int mx_node = std::max(p, q);
        if (mx_node >= static_cast<int>(links.size())) {
            links.resize(mx_node + 1);
        }
        links[p].push_back(q); 
    }
    std::vector<double> pagerank(links.size(), 1.0 / links.size());
    for (int cycle = 0; cycle < 50; ++cycle) {
        std::vector<double> new_pagerank(links.size(), 0.0);
        double dscore = 0.0;
        for (int i = 0; i < links.size(); ++i) {
            if (links[i].empty()) {
                dscore += pagerank[i] / links.size();
            } else {
                for (int j : links[i]) {
                    new_pagerank[j] += pagerank[i] / links[i].size();
                }
            }
        }

        for (int i = 0; i < links.size(); ++i) {
            new_pagerank[i] = (1 - ALP) / links.size() + ALP * (new_pagerank[i] + dscore);
        }

        pagerank = new_pagerank;
    }
    double sum_scores = 0.0;
    for (int i = 0; i < links.size(); ++i) {
        std::cout << i << " = " << pagerank[i] << std::endl;
        sum_scores += pagerank[i];
    }

    std::cout << "s = " << sum_scores << std::endl;
}
