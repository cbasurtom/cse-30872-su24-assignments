// Challege 06: Distinct Fruit

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

// Constants

// Functions

vector<string> distinct_fruit(vector<string> fruits) {

    vector<string>        current_sequence;
    vector<string>        longest_sequence(0);
    set<string>           seen_fruits;

    // Check every fruit
    for (const auto& fruit : fruits) {
        // Fruit has not been seen before
        if (seen_fruits.find(fruit) == seen_fruits.end()) {
            seen_fruits.insert(fruit);
            current_sequence.push_back(fruit);
        } else {
            while (!current_sequence.empty() && current_sequence.front() != fruit) {
                seen_fruits.erase(current_sequence.front());
                current_sequence.erase(current_sequence.begin());
            }
            current_sequence.erase(current_sequence.begin());
            current_sequence.push_back(fruit);
        }

        // Update longest sequence
        if (longest_sequence.size() < current_sequence.size()) longest_sequence = current_sequence;
    }
    return longest_sequence;

}

// Main execution

int main(int argc, char *argv[]) {

    string         line, fruit;
    vector<string> fruits;

    while (getline(cin, line)) {
        stringstream ss(line);

        fruits.clear();
        while(ss >> fruit) fruits.push_back(fruit);

        vector<string> dist_fruits = distinct_fruit(fruits);

        cout << dist_fruits.size() << ": ";

        if (dist_fruits.size() > 1) for (int i = 0; i < int(dist_fruits.size()) - 1; i++ ) cout << dist_fruits[i] << ", ";

        cout << dist_fruits.back() << endl; 

    }
    
    return 0;
}