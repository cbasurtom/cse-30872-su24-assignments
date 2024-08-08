// Challege 02: Supercalifragilisticexpialidocious

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

// Functions

int app_times(multiset<char> s1, multiset<char> s2) {

    int count = 0;

    while (true) {
        for (auto y : s2) {
            auto it = s1.find(y);
            if (it == s1.end()) {
                return count;
            }
            s1.erase(it);
        }
        count++;
    }

}

// Main execution

int main(int argc, char *argv[]) {

    string line, str1, str2;

    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> str1 >> str2;

        multiset<char> s1(str1.begin(), str1.end());
        multiset<char> s2(str2.begin(), str2.end());

        cout << app_times(s1, s2) << endl;

    }

    return 0;
}