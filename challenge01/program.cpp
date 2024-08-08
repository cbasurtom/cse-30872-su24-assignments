// Challege 01: Minimum Four Square

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;

// Constants

const size_t NLETTERS = 26;

// Functions

int min_four_square(vector<int> &mat, int n, int m) {

    int min_four_square = 999;
    int temp = 999;

    for (int i = 0; i < (n-1); i++) {
        for (int j = 0; j < (m-1); j++){
            temp = mat[i*m+j] + mat[i*m+j+1] + mat[(i+1)*m+j] + mat[(i+1)*m+j+1];
            min_four_square = (temp <= min_four_square) ? temp : min_four_square;
        }
    }

    return min_four_square;
}

// Main execution

int main(int argc, char *argv[]) {

    string line;
    int n, m, e;
    int index = 1;

    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> n >> m;

        if ((n == 0) and (m == 0)) break;

        vector<int> mat;
        mat.reserve(n*m);

        for (int i = 0; i < n; i++) {
            getline(cin, line);
            stringstream ss(line);
            for (int j = 0; j < m; j++) {
                ss >> e;
                mat.push_back(e);
            }
        }

        int sol = min_four_square(mat, n, m);
        cout << index << ". Minimum four square is: " << sol << endl;
        index++;
    }

    return 0;
}