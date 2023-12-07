#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll ma = 0, cur = 0;
    string s;
    while (true)
    {
        getline(cin, s);
        if (s == "-1" || s.empty())
        {
            ma = max(ma, cur);
            cur = 0;
            if (s == "-1")
                break;
        }
        else
            cur += stoi(s);
    }
    cout << ma << '\n';

    return 0;
}

