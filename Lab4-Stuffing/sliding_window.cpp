// CPP Program to implement Sliding Window Protocol

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int i, j, k, n, m, count = 0, flag = 0;
    string s, r;
    cout << "Enter the data to be sent: ";
    cin >> s;
    cout << "Enter the window size: ";
    cin >> n;
    m = s.length();
    for (i = 0; i < m; i = i + n)
    {
        if (i + n < m)
            cout << "The " << ++count << " window is " << s.substr(i, n) << endl;
        else
            cout << "The " << ++count << " window is " << s.substr(i, m - i) << endl;
        cout << "Do you want to send this window (y/n)? ";
        cin >> r;
        if (r == "n")
        {
            cout << "Enter the number of the window to be resent: ";
            cin >> k;
            i = (k - 2) * n;
        }
    }
    return 0;
}