#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<char, int> val = {{'A', 1},
                                {'B', 2},
                                {'C', 3},
                                {'X', -1},
                                {'Y', 0},
                                {'Z', 1}};

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
        char chr1 = s[0], chr2 = s[2];
        int val2 = (val[chr1]+val[chr2])%3;
        if (val2 == 0)
            val2 = 3;
        if (chr2 != 'X')
            sum += (chr2 == 'Y'?3:6);
        sum += val2;
    }
    cout << sum << '\n';

    return 0;
}
