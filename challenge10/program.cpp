#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

// Function to calculate minimum operations
long long min_ops(long long n, unordered_map<long long, long long>& memo) {
    if (n == 1) return 0;
    if (memo.count(n)) return memo[n];

    long long res;
    if (n % 2 == 0) {
        res = 1 + min_ops(n / 2, memo);
    } else {
        res = 1 + min(min_ops(n - 1, memo), min_ops(n + 1, memo));
    }

    memo[n] = res;
    return res;
}

int main() {
    string line;
    int counter = 1;

    while (getline(cin, line)) {
        stringstream ss(line);
        long long n;
        ss >> n;

        unordered_map<long long, long long> memo;
        long long result = min_ops(n, memo);

        cout << counter << ". " << result << endl;
        counter++;
    }

    return 0;
}
