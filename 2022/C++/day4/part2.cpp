#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll res = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while (true)
    {
        string s;
        cin >> s;
        if (s == "-1")
            break;
        stringstream ss(s);
        int l1, r1, l2, r2;
        char _;
        ss >> l1 >> _ >> r1 >> _ >> l2 >> _ >> r2;
        if (!(r1 < l2 || r2 < l1))
            res++;
    }
    cout << res << '\n';

    return 0;
}


