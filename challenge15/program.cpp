// Challenge 15: Maximum Concurrency

#include <iostream>
#include <sstream>
#include <queue>
#include <tuple>
#include <deque>
#include <vector>

using namespace std;

// Node structure

template <typename T>
struct Node {
    T	  value;
    Node *left;
    Node *right;

    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Functions

// Build binary tree with preorder input
template <typename T>
Node<T>* buildTree(deque<int>& preorder, int& index) {
    if (index >= int(preorder.size()) || preorder[index] == -1) {
        index++;
        return nullptr;
    }
    
    int val = preorder[index++];
    Node<T>* node = new Node<T>(val);
    node->left = buildTree<T>(preorder, index);  
    node->right = buildTree<T>(preorder, index);
    
    return node;
}

template <typename T>
deque<int> bfs(Node<T>* root) {
    deque<Node<T>*> q;
    deque<int> bfs_tree;

    if (root == nullptr) {
        bfs_tree.push_back(-1);
        return bfs_tree;
    }

    q.push_back(root);

    while (!q.empty()) {
        int level_size = q.size();
        bool all_null = true;

        for (int i = 0; i < level_size; ++i) {
            Node<T>* node = q.front();
            q.pop_front();

            if (node != nullptr) {
                bfs_tree.push_back(node->value);
                q.push_back(node->left);
                q.push_back(node->right);

                if (node->left != nullptr || node->right != nullptr) {
                    all_null = false;
                }
            } else {
                bfs_tree.push_back(-1);
                q.push_back(nullptr);
                q.push_back(nullptr);
            }
        }

        // If all nodes in the current level were null, we're done
        if (all_null) break;
    }

    return bfs_tree;
}


tuple<int, int> max_conc(const deque<int>& tree) {

    int curr_level = 0;
    int curr_nodes = 0;
    int max_level  = 0;
    int max_nodes  = 0;

    for (int i = 0; i < int(tree.size()); i++) {
        // Move on to next level
        int x = i+1;
        if (i == 0 || ((x & (x - 1)) == 0)) {
            curr_level++;
            curr_nodes = 0;
        }

        // If not null, count
        if (tree[i] != -1) curr_nodes++;

        // Update max
        if (curr_nodes > max_nodes) {
            max_nodes = curr_nodes;
            max_level = curr_level;
        }

    }

    return make_tuple(max_level, max_nodes);
}

// Main execution

int main(int argc, char* argv[]) {
    string line;
    int num;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        deque<int> tree, bfs_tree;
        
        while (ss >> num) tree.push_back(num);

        int index = 0;

        // Build tree 
        Node<int>* root = buildTree<int>(tree, index);

        bfs_tree = bfs(root);

        tuple<int, int> maxes = max_conc(bfs_tree);
        int max_level = get<0>(maxes);
        int max_nodes = get<1>(maxes);
        cout << "Level " << max_level << " has the most nodes: " << max_nodes << endl;

        delete root;
        tree.clear();
        bfs_tree.clear();
    }

    return 0;
}
