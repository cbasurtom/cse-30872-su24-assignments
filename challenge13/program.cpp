// Challenge 13: Taeho's Tree

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

// Functions

void bst_bfs(const deque<int>& q, deque<deque<int>>* levels, int level = 0) {
    
    // Base case, end of tree
    if (q.size() == 0) return;
    
    if (levels->size() <= (long unsigned int)level) levels->emplace_back();

    // Print current node
    long unsigned int index = q.size() / 2;
    int root = q[index];
    (*levels)[level].push_back(root);

    // Left side
    if (index > 0) {
        deque<int> l_q(q.begin(), q.begin() + index);
        bst_bfs(l_q, levels, level + 1);
    }

    // Right side
    if (index + 1 < q.size()) {
        deque<int> r_q(q.begin() + index + 1, q.end());
        bst_bfs(r_q, levels, level + 1);
    }
    
    return;
}

// Main execution

int main(int argc, char *argv[]) {
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        int value;
        deque<int> q;
        deque<deque<int>> levels;

        while (ss >> value) {
            q.push_back(value);
        }

        bst_bfs(q, &levels);

        // Print each level
        for (const auto& level : levels) {
            for (long unsigned int i = 0; i < level.size()-1; i++) {
                cout << level[i] << " ";
            }
            cout << level[level.size()-1] << endl;
        }
    }

    return 0;
}
