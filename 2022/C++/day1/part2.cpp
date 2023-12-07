#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll cur = 0;
    vector<ll> ma;
    string s;
    while (true)
    {
        getline(cin, s);
        if (s == "-1" || s.empty())
        {
            ma.push_back(cur);
            for (int i = ma.size()-1; i > 0; i--)
            {
                if (ma[i] > ma[i-1])
                    swap(ma[i], ma[i-1]);
            }
            if (ma.size() > 3) ma.pop_back();
            cur = 0;
            if (s == "-1")
                break;
        }
        else
            cur += stoi(s);
    }
    cout << ma[0]+ma[1]+ma[2] << '\n';

    return 0;
}

