// Challenge 09: Seb's Horchata Hustle

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;

// Constants

// Functions

bool readline(deque<int> &v) {

    string line;
    if (!getline(cin, line)) return false;
    
    stringstream ss(line);

    int num;
    while (ss >> num) {
        v.push_back(num);
    }

    return true;
}

bool correct_change(deque<int> &cash) {

    multiset<int> change;

    // While there are customers left
    while(!cash.empty()) {
        // If they pay exactly, no change needed
        if (cash[0] == 5) {
            change.insert(5);
        // If paid with $10, one $5 needed
        } else if (cash[0] == 10) {
            if (change.find(5) ==  change.end()) return false;
            change.insert(10);
            change.erase(change.find(5));
        // If paid with $20, change must be either $10 and $5 or three $5
        } else {
            // No $10
            if (change.find(10) == change.end()) {
                if (change.count(5) < 3) return false;
                for (int i = 0; i < 3; i++) change.erase(change.find(5));
            // Has a $10
            } else {
                if (change.find(5) ==  change.end()) return false;
                change.erase(change.find(5));
                change.erase(change.find(10));
            }

            change.insert(20);
        }

        cash.pop_front();
    }

    return true;
}

// Main execution
int main(int argc, char *argv[]) {
    int        counter = 1;
    string     line, answer;
    deque<int> cash;

    while (readline(cash)) {
        
        answer = (correct_change(cash)) ? "Yeah" : "Nope";

        cout << counter << ". " << answer << endl;

        counter++;

        cash.clear();

    }

    return 0;
}