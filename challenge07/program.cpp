// Challenge07: Knight's Dialer

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Constants

// Functions

void phone_combinations(int pos, int hops, string path) {
    // TODO: Recursively display combinations

    map<int, string> mapping;
    mapping[1] = "68";
    mapping[2] = "79";
    mapping[3] = "48";
    mapping[4] = "039";
    mapping[5] = "";
    mapping[6] = "017";
    mapping[7] = "26";
    mapping[8] = "13";
    mapping[9] = "24";
    mapping[0] = "46";
    
    //cout << "Current string: " << path << endl;

    // Add current position to path
    path += to_string(pos);

    // Base case: no more hops
    if (hops == 1) { cout << path << endl; return;}

    // Recursive case: hops remain
    else {
        // Check available steps to path based on position
        string possible_paths = mapping[pos];
        
        // Traverse every possible path
        for (char step : possible_paths) {
            phone_combinations(atoi(&step), hops-1, path);
        }
        
    }


}

// Main execution

int main(int argc, char *argv[]) {
    string line;
    
    while (getline(cin, line)) {
        stringstream ss(line);

        if (ss.str().empty()) {
            cout << "";
            continue;
        }
        
        int start = 0, hops = 0;
        
        ss >> start >> hops;
        phone_combinations(start, hops, "");
        if (cin.peek() != EOF) cout << endl;
    }

    return 0;
}