// Challenge 08: Masked Bit

#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <cctype>

using namespace std;

// Constants

// Functions

int appearances(const bitset<4>& mask, const bitset<32>& bitstream) {

    int apps = 0;

    for (int i = 0; i < 32; i++) {
        if (mask[0] == bitstream[i] and i+3 < 32) {
            if (mask[1] == bitstream[i+1] and mask[2] == bitstream[i+2] and mask[3] == bitstream[i+3]) apps++;
        }
    }

    return apps;
}

// Main execution
int main(int argc, char *argv[]) {
    int       counter = 1, intstream;
    string    line;
    

    while (getline(cin, line)) {
        stringstream ss(line);
        
        unsigned long long hexmask;

        ss >> hex >> hexmask;
        ss >> dec >> intstream;

        bitset<4>  mask(hexmask);
        bitset<32> bitstream(intstream);;

        stringstream hexnum;
        hexnum << hex << hexmask;
        string hexstring = hexnum.str();

        if (isalpha(hexstring[0])) hexstring[0] = toupper(hexstring[0]);

        cout << counter << ". " << intstream << " contains 0x" << hexstring << " " << appearances(mask, bitstream) << " times" << endl;

        counter++;

    }

    return 0;
}