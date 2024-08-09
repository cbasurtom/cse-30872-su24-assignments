// Challege 02: HTML Tags

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>

using namespace std;

// Constants

// Functions

bool is_balanced(string line) {
    stack<string> s;
    string tag = "";
    bool tag_it = false;
    bool closing = false;

    for (auto ch : line) {
        if (ch == '<') {
            tag_it = true;
            closing = false;
            tag = "";  // start a new tag
        } else if (ch == '>') {
            tag_it = false;
            if (closing) {
                if (s.empty() || s.top() != tag) return false;
                s.pop();
            } else {
                s.push(tag);
            }
        } else if (tag_it) {
            if (ch == '/') {
                if (tag.empty()) {
                    closing = true;
                } else {
                    tag += ch;
                }
            } else {
                tag += ch;  // accumulate tag name
            }
        }
    }

    return s.empty();
}

// Main execution

int main(int argc, char *argv[]) {

    string line;

    while(getline(cin, line)) {
        if (is_balanced(line)) cout << "Balanced" << endl;
        else cout << "Unbalanced" << endl;
    }

    return 0;
}