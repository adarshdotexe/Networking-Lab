// CPP Program to implement Character Stuffing

#include <iostream>
#include <string>

using namespace std;

int main() {
    string input, flag, escape, output = "";
    cout << "Enter the input string: ";
    cin >> input;
    cout << "Enter the flag: ";
    cin >> flag;
    cout << "Enter the escape character: ";
    cin >> escape;

    // Add the flag at the beginning of the input string
    output += flag;

    // If the input character is the same as the flag or escape character, then add the escape character before it
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == flag[0]) {
            output += escape;
        }
        output += input[i];
        if (input[i] == escape[0]) {
            output += escape;
        }
    }

    // Add the flag at the end of the input string
    output += flag;

    cout << "Output: " << output << endl;

    return 0;
}
