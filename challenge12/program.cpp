// Challenge 12: Kakamora

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

// Constants

// Functions
vector<vector<int>> min_kakamora(vector<vector<int>> ocean) {
    
    // Initialize table
    vector<vector<int>> kakamora(ocean.size()+1, vector<int>(ocean.size()+1, 999));

    // Base case
    kakamora[0][0] = 0;
    kakamora[1][1] = ocean[0][0];

    for (long unsigned int i = 0; i < ocean.size(); i++) {
        for (long unsigned int j = 0; j < ocean.size(); j++) {
            vector<int> nav_options;
            // Check north
            nav_options.push_back(kakamora[i][j+1]);
            // Check east
            nav_options.push_back(kakamora[i+1][j]);
            // Check northeast
            nav_options.push_back(kakamora[i][j]);

            kakamora[i+1][j+1] = ocean[i][j] + *min_element(nav_options.begin(), nav_options.end());
        }
    }
    
    return kakamora;
}

deque<int> find_path(vector<vector<int>> kakamora, vector<vector<int>> ocean) {
    
    deque<int> path;

    int row = kakamora.size()-1;
    int col = kakamora.size()-1;

    while (row > 0 and col > 0) {
        // Add current position to path
        path.push_front(ocean[row-1][col-1]);

        // Consider where we came from
        // Prioritize horizontal>vertical>diagonal
        int hori = kakamora[row][col-1];
        int vert = kakamora[row-1][col];
        int diag = kakamora[row-1][col-1];
        if (hori <= vert) {
            if (hori <= diag) { col--; continue;}
            else { col--; row--; continue;}
        } else if (vert <= diag) { row--; continue;}
        else { col--; row--; continue; }
    }

    return path;
}


// Main execution
int main(int argc, char *argv[]) {

    vector<vector<int>> ocean;
    vector<vector<int>> kakamora;
    vector<int>         row;
    deque<int>          path;
    string              line;
    int                 num;

    while(getline(cin, line)) {
        stringstream ss(line);
        ss >> num; 

        if (num == 0) break;

        // Record matrix
        for (int i = 0; i < num; i++) {
            if (getline(cin, line)) {
                stringstream ss(line);
                int value;
                while (ss >> value) row.push_back(value);
                ocean.push_back(row);
                row.clear();  // Clear row for the next line
            }
        }

        kakamora = min_kakamora(ocean);

        // Print min kakamora
        cout << kakamora[num][num] << endl;

        path = find_path(kakamora, ocean);

        for (long unsigned int i = 0; i < path.size()-1; i++) cout << path[i] << " ";
        cout << path[path.size()-1] << endl;

        kakamora.clear();
        ocean.clear();
        path.clear();

    }

    return 0;
    
}