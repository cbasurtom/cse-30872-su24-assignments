// Challege 05: Selina's Medicine

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <algorithm>

using namespace std;

using Bottle = tuple<string, string, string, char>;

// Constants

// Functions

// Main execution

int main(int argc, char *argv[]) {

    int            num;
    char           rsize;
    string         result = "", line;
    vector<Bottle> gel_bottles, tablet_bottles;
    
    for (int i = 0; i < 1000; i++) {
        // Get number of bottles
        getline(cin, line);
        stringstream ss(line);
        ss >> num;

        // Read bottle details
        for (int i = 0; i < num; i++) {
            getline(cin, line);
            stringstream ss(line);

            string name, size, type;

            ss >> name >> size >> type; 

            if (size == "small")  rsize = 'a';
            if (size == "medium") rsize = 'b';
            if (size == "large")  rsize = 'c';
    
            if (type == "gel") gel_bottles.push_back(make_tuple(name, size, type, rsize));
            else tablet_bottles.push_back(make_tuple(name, size, type, rsize));
        }

        // Sort bottles: first by name, then by size
        auto sortBottles = [](vector<Bottle>& bottles) {
            sort(bottles.begin(), bottles.end(),
                [](const Bottle& a, const Bottle& b) {
                    if (get<0>(a) != get<0>(b))
                        return get<0>(a) < get<0>(b); // Sort by name
                    return get<3>(a) < get<3>(b); // Sort by size
                }
            );
        };

        // Sort gel and tablet bottles
        sortBottles(gel_bottles);
        sortBottles(tablet_bottles);

        for (const auto& bottle : gel_bottles) {
            if (get<3>(bottle) == 'a') result += ".";
            if (get<3>(bottle) == 'b') result += ":";
            if (get<3>(bottle) == 'c') result += "|";
        }
        for (const auto& bottle : tablet_bottles) {
            if (get<3>(bottle) == 'a') result += ".";
            if (get<3>(bottle) == 'b') result += ":";
            if (get<3>(bottle) == 'c') result += "|";
        }

        cout << result << endl;

        result.clear();
        gel_bottles.clear();
        tablet_bottles.clear();

    }
    
    return 0;
}