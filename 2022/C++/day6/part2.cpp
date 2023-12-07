#include <bits/stdc++.h>
using namespace std;

int res = -1;
bool found = false;
string input;
map<char, int> freq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("INPUT.INP", "r", stdin);
    cin >> input;
    for (int i = 0; i < 13; i++)
        freq[input[i]]++;
    for (int i = 13; i < input.size(); i++)
    {
        string marker = input.substr(i-13, 14);
        if (i >= 14)
            freq[input[i-14]]--;
        freq[input[i]]++;
        found = true;
        for (int i = 0; i < marker.size()-1; i++)
                found &= freq[marker[i]] == 1;
        if (found)
        {
            res = i+1;
            break;
        }
    }
    cout << res << '\n';

    return 0;
}


