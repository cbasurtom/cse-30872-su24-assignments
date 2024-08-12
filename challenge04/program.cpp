// Challege 04: Sam's Search

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Constants

// Functions

int is_found(int target, vector<int> num_array) {
    
    int start = 0;
    int end   = num_array.size() - 1;

    while (start <= end) {

        int index = (start + end) / 2;

        if (num_array[index] == target) return index;

        // Left side is sorted
        if (num_array[start] <= num_array[index]) {
            // Target is in left side
            if ((target < num_array[index]) and (target >= num_array[start])) end = index - 1;
            // Target is in right side
            else start = index + 1;
        // Right side is sorted
        } else {
            // Target is in right side
            if ((target > num_array[index]) and (target <= num_array[end])) start = index + 1;
            // Target is in left side
            else end = index - 1;
        }
    }

    return -1;
}

// Main execution

int main(int argc, char *argv[]) {

    int         num, target;
    string      line;
    vector<int> num_array;
    

    while(getline(cin, line)) {
        stringstream ss_arr(line);

        while (ss_arr >> num) num_array.push_back(num);

        getline(cin,line);
        stringstream ss_tar(line);
        ss_tar >> target;

        int index = is_found(target, num_array);

        if (index != -1) cout << target << " found at index " << index << endl;
        else cout << target << " was not found" << endl;

        num_array.clear();
    }

    return 0;
}