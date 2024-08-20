// Challenge 14: Binary Christmas Tree

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <bitset>

using namespace std;

// Functions

// Return number of paths possible in binary christmas tree
int paths(const deque<int>& tree, const deque<int>& path, int t_index, int p_index, deque<int>* totals) {

    int found_paths = 0;
    
    // Base case: end of tree
    if (t_index >= int(tree.size())) return 0;

    // If match, continue
    if (tree[t_index] == path[p_index]) {
        // If end of path, +1 to total, reset path and keep going
        if (p_index == int(path.size()-1)) {
            if ((*totals)[t_index] == 0) {
                found_paths++;
                (*totals)[t_index] = 1;
            }
            // Check if overlap
            if (tree[t_index] == path[0] and path.size() > 1) {
                found_paths += paths(tree, path, 2*t_index+1, 1, totals);
                found_paths += paths(tree, path, 2*t_index+2, 1, totals);
            } else {
                found_paths += paths(tree, path, 2*t_index+1, 0, totals);
                found_paths += paths(tree, path, 2*t_index+2, 0, totals);
            }
        }
        // Not end of path, continue with children
        else {
            found_paths += paths(tree, path, 2*t_index+1, p_index+1, totals);
            found_paths += paths(tree, path, 2*t_index+2, p_index+1, totals);

            // Check if overlap
            if (tree[t_index] == path[0] and path.size() > 1) {
                found_paths += paths(tree, path, 2*t_index+1, 1, totals);
                found_paths += paths(tree, path, 2*t_index+2, 1, totals);
            }
        }
    } else {
        // If no match, check if match in the children
        
        // Check if overlap
        if (tree[t_index] == path[0]) {
            found_paths += paths(tree, path, 2*t_index+1, 1, totals);
            found_paths += paths(tree, path, 2*t_index+2, 1, totals);
        } else {
            found_paths += paths(tree, path, 2*t_index+1, 0, totals);
            found_paths += paths(tree, path, 2*t_index+2, 0, totals);
        }
    }

    return found_paths;
}

// Main execution

int main(int argc, char *argv[]) {
    string line;

    while (getline(cin, line)) {
        int        target;
        string     tree, binary_str;
        deque<int> q, path, totals;

        stringstream ss(line);
        ss >> target;
        ss >> tree;


        // Special case: 0
        if (target == 0) {
            binary_str = "0";
        }
        else {
            // Calculate target in binary
            bitset<32> binary(target);
            binary_str = binary.to_string();

            // Trim leading zeros
            size_t firstNonZero = binary_str.find_first_not_of('0');
            if (firstNonZero != std::string::npos) {
                binary_str = binary_str.substr(firstNonZero);
            }
        }

        for (auto num : tree) { q.push_back(num - '0'); totals.push_back(0); }
        for (auto let : binary_str) path.push_back(let - '0');

        cout << "Paths that form " << target << " in binary (" << binary_str << "): " << paths(q, path, 0, 0, &totals) << endl;
    }

    return 0;
}