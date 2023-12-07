#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<char, int> val = {{'A', 1},
                                {'B', 2},
                                {'C', 3},
                                {'X', 1},
                                {'Y', 2},
                                {'Z', 3}};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    ll sum = 0;
    while (true)
    {
        getline(cin, s);
        if (s == "-1")
            break;
        int val1 = val[s[0]], val2 = val[s[2]];
        sum += val2;
        switch ((val2-val1+3)%3)
        {
            case 1: // you win
            {
                sum += 6;
                break;
            }
            case 0: // draw
            {
                sum += 3;
                break;
            }
            // you lose dont change the sum
        }
    }
    cout << sum << '\n';

    return 0;
}
