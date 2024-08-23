// Challenge 18: Mike's Spanning Trees

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

// Constants

const int INF = 1e9;

// Functions

char numberToLetter(int num) {
    return 'A' + num;
}

vector<set<pair<int,int>>> read_adj(int vertices) {

    vector<set<pair<int,int>>> adj(vertices);
    string line;

    // Read matrix
    for (int i = 0; i < vertices; i++) {
        getline(cin, line);
        stringstream row(line);
        int c;
        for (int j = 0; j < vertices; j++) {
            row >> c;
            if (c == -1) continue;
            adj[i].insert({j, c});
            adj[j].insert({i, c}); // Undirected, so both directions
        }
    }

    // Print matrix
    // for (int i = 0; i < int(adj.size()); i++) {
    //     cout << i << ": ";
    //     for (auto p : adj[i]) cout << "(" << p.first << "," << p.second << ") ";
    //     cout << endl;
    // }

    return adj;
}

pair<int, vector<string>> prims(const vector<set<pair<int,int>>>& adj) {

    // Construct distance array
    vector<int> distance(adj.size(), INF);

    // Initialize priority queue: weight, node
    priority_queue<tuple<int, int>> q;

    // Initialize starting point
    distance[0] = 0;
    tuple<int, int> step = {0, 0};

    q.push(step);

    // Initialize visited array
    vector<bool>        visited(int(adj.size()), false);

    // Initialize path array
    vector<int> tree(int(adj.size()), -1);

    while (!q.empty()) {
        tuple<int, int> top = q.top();
        int a = get<1>(top);

        q.pop();

        if (visited[a]) continue;

        visited[a] = true;

        for (auto neighbor : adj[a]) {
            int  b      = get<0>(neighbor);
            int  w      = get<1>(neighbor);

            if (!visited[b] && w < distance[b]) {
                distance[b] = w;
                q.push({-distance[b], b});
                tree[b] = a;
            }
        }

    }

    int cost = 0;

    for (auto dist : distance) cost+= dist;

    vector<string> mst;

    // Print the edges of the MST
    for (int i = 1; i < int(adj.size()); ++i) {
        char source = numberToLetter(tree[i]);
        char dest   = numberToLetter(i);
        if (source > dest) swap(source, dest);
        string step = string(1, source) + dest;
        mst.push_back(step);
    }

    sort(mst.begin(), mst.end());

    // for (auto b : mst) cout << b << endl;
        
    pair<int, vector<string>> answer = {cost, mst};

    return answer;
}

// Main execution

int main(int argc, char* argv[]) {
    string line;
    bool first = true;

    while (getline(cin, line)) {

        if (!first) cout << endl;
        first = false;

        // Extract vertices
        stringstream ss(line);
        int vertices;
        ss >> vertices;

        // Construct adjacency list
        vector<set<pair<int,int>>> adj = read_adj(vertices);

        // Use Prim's Algorithm to find MST and path
        pair<int, vector<string>> answer = prims(adj);

        int cost = answer.first;
        vector<string> mst = answer.second;

        cout << cost << endl;
        for (int i = 0; i < int(mst.size()); i++) cout << mst[i] << endl;
        

    }

    return 0;

}