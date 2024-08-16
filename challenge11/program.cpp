#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

// Function to calculate minimum operations
long long min_ops(long long target, long long money, unordered_map<string, long long>& memo) {
    
    // Base case, found target
    if (target == money) return 0;

    string key = to_string(money);

    // Base case, already in table
    if (memo.count(key)) return memo[key];

    // Recursive case, not in table
    long long res;
    if ((money*2 != 0) && (money*2 <= target)) {
        long long timestwo = min_ops(target, money*2, memo);
        long long plusone = min_ops(target, money+1, memo);
        res = min(timestwo, plusone) + 1;
    } else res = min_ops(target, money+1, memo) + 1;

    // Add to table
    memo[key] = res;
    return res;
}

int main() {
    string line;
    int counter = 1;

    while (getline(cin, line)) {
        stringstream ss(line);
        long long n;
        ss >> n;

        unordered_map<string, long long> memo;
        long long result = min_ops(n, 0, memo);

        cout << counter << ". Minimum number of doge transactions: " << result << endl;
        counter++;
    }

    return 0;
}
