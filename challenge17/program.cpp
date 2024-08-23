// Challenge 17: A-Mazing Paths

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <queue>
#include <set>

using namespace std;

// Constants

const int INF = 1e9;

// Functions

vector<char> read_maze(int rows, int cols) {

    vector<char> maze(rows * cols);
    string line;

    // First pass: Read maze and store cell types
    for (int i = 0; i < rows; i++) {
        getline(cin, line);
        stringstream row(line);
        char c;
        for (int j = 0; j < cols; j++) {
            row >> c;
            maze[j + i * cols] = c;
        }
    }

    // Print maze
    // for (int i = 0; i < int(maze.size()); i++) {
    //     if (i%cols == 0) cout << endl;
    //     cout << maze[i] << " ";
    // }
    // cout << endl;

    return maze;
}

vector<vector<tuple<int,int,bool, bool>>> read_adjl(int rows, int cols, const vector<char>& maze) {
    
    vector<vector<tuple<int,int,bool, bool>>> adj(rows*cols);

    // Second pass: Build the adjacency list
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            char space = maze[j + i * cols];

            // Skip blocked space
            if (space == '1') continue;

            // Check if ending
            bool target = (space == 'E');

            // Check if start
            bool start  = (space == 'S');
                
            // Check available neighbors
            int curr_index = j+i*cols;

            // Direction vectors for 4 directions (down, right, down-right diagonal and left-down diagonal)
            int dRow[] = {1, 0, 1,  1};
            int dCol[] = {0, 1, 1, -1};
            int dDia[] = {0, 0, 1,  1};
                
            for (int k = 0; k < 4; k++) {
                int newRow = i + dRow[k];
                int newCol = j + dCol[k];

                // Ensure within bounds 
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    int  neighbor_index = newCol + newRow * cols;
                    char neighbor_space = maze[neighbor_index];

                    // Skip blocked neighbor
                    if (neighbor_space == '1') continue;

                    // Check if neighbor is ending 
                    bool neighbor_target = (neighbor_space == 'E');

                    // Check if neighbor is start
                    bool neighbor_start  = (neighbor_space == 'S');

                    // Determine weight
                    bool diag = (dDia[k] == 1);
                    int w = (diag) ? 2 : 1;

                    adj[curr_index].push_back({neighbor_index, w, neighbor_target, neighbor_start});
                    adj[neighbor_index].push_back({curr_index, w, target, start}); // Since graph is undirected, both are added
                }
            }

        }
    }

    // Print out the adjacency list
    // for (int i = 0; i < int(adj.size()); i++) {
    //     if (adj[i].empty()) {
    //         // Node with no neighbors
    //         cout << "Node " << i << ": No neighbors" << endl;
    //     } else {
    //         cout << "Node " << i << ": ";
    //         for (const auto& edge : adj[i]) {
    //             int neighbor_index, weight;
    //             bool is_target;
    //             tie(neighbor_index, weight, is_target) = edge;
    //             cout << "(Neighbor: " << neighbor_index
    //                  << ", Weight: " << weight
    //                  << ", Target: " << (is_target ? "Yes" : "No") << ") ";
    //         }
    //         cout << endl;
    //     }
    // }

    return adj;
}

pair<int, vector<int>> dijkstras(const vector<vector<tuple<int,int,bool, bool>>>& adj, int start) {

    // Construct distance array
    vector<int> distance(adj.size(), INF);

    // Initialize priority queue: weight, node, path
    priority_queue<tuple<int, int, vector<int>>> q;

    // Initialize starting point
    distance[start] = 0;
    vector<int> path;
    tuple<int, int, vector<int>> step = {0, start, path};

    q.push(step);

    // Initialize visited array
    vector<bool>        visited(int(adj.size()), false);

    // Initialize target array
    vector<bool>        targets(int(adj.size()), false);

    // Initialize path array
    vector<vector<int>> paths(int(adj.size()));

    while (!q.empty()) {
        tuple<int, int, vector<int>> top = q.top();
        int a = get<1>(top);
        vector<int> path = get<2>(top);

        q.pop();

        if (visited[a]) continue;

        visited[a] = true;

        for (auto neighbor : adj[a]) {
            int  b      = get<0>(neighbor);
            int  w      = get<1>(neighbor);
            bool target = get<2>(neighbor);

            if (target) targets[b] = true;

            if (distance[a]+w < distance[b]) {
                distance[b] = distance[a]+w;
                path.push_back(a);
                paths[b].clear();
                for (auto p : path) paths[b].push_back(p);
                q.push({-distance[b], b, path});
                path.pop_back();
            }
        }
    }

    int         cost = INF;
    vector<int> final_p; 

    // Verify shortest path to a target
    for (int i = 0; i < int(adj.size()); i++) {
        if (targets[i]) {
            if (distance[i] < cost) {
                cost = distance[i];
                final_p.clear();
                final_p = paths[i];
                final_p.push_back(i);
            }
        }
    }
    
    if (cost == INF) cost = 0;
    pair<int, vector<int>> result = {cost, final_p};

    return result;

}

// Main execution

int main(int argc, char* argv[]) {
    string line;

    while (getline(cin, line)) {
        // Dimensions of board
        int rows, cols;

        stringstream ss(line);

        ss >> rows >> cols;

        // End of game
        if (rows == 0 && cols == 0) break;

        // Initialize a vector to store the type of each cell ('1', '0', 'S', 'E')
        vector<char> maze = read_maze(rows, cols);

        // Initialize adjacency list representation with node, weight and target status
        vector<vector<tuple<int,int,bool, bool>>> adj = read_adjl(rows, cols, maze);

        // Initialize list of starts
        set<int> starts;

        // Use Dijkstra's Algorithm to find the shortest path and its cost from all starts
        for (int i = 0; i < int(adj.size()); i++) {
            for (auto n_list : adj) {
                for (auto neighbor : n_list) {
                    int  b     = get<0>(neighbor);
                    bool start = get<3>(neighbor);
                    if (start) starts.insert(b);
                }
            }
        }

        pair<int, vector<int>> p_answer;
        vector<int>            path;
        int                    cost = INF;

        for (auto start : starts) {
            pair<int, vector<int>> p_answer = dijkstras(adj, start);
            int p_cost = p_answer.first;
            if (p_cost < cost) {
                path = p_answer.second;
                cost = p_cost;
            }
        }

        if (cost == INF) cost = 0;
        
        // Print result
        cout << "Cost: " << cost << " ";
        cout << "Path: ";
        if (path.empty()) cout << "None"; 
        else {
            for (int i = 0; i < int(path.size() - 1); i++) cout << path[i] << " ";
            cout << path[path.size()-1];
        }
        cout << endl;

    }

    return 0;

}