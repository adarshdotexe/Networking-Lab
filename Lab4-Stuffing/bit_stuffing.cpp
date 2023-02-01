// CPP Program to implement Bit Stuffing

#include <iostream>
#include <string>

using namespace std;

int main() {
    string input, output = "";
    cout << "Enter the input string: ";
    cin >> input;

    int count = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '1') {
            count++;
        } else {
            count = 0;
        }
        output += input[i];
        if (count == 5) {
            output += '0';
            count = 0;
        }
    }

    cout << "Output: " << output << endl;

    return 0;
}