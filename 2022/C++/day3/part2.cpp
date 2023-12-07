#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    int cur = 0;
    ll res = 0;
    map<char, bool> check[3];
    while (true)
    {
        cin >> s;
        if (s == "-1")
            break;
        for (int i = 0; i < s.size(); i++)
            check[cur][s[i]] = true;
        cur++;
        if (cur == 3)
        {
            for (char chr = 'a'; chr <= 'z'; chr++)
                if (check[0][chr] && check[0][chr] == check[1][chr] && check[1][chr] == check[2][chr])
                {
                    res += chr-'a'+1;
                    break;
                }
            for (char chr = 'A'; chr <= 'Z'; chr++)
                if (check[0][chr] && check[0][chr] == check[1][chr] && check[1][chr] == check[2][chr])
                {
                    res += chr-'A'+27;
                    break;
                }
            cur = 0;
            for (int i = 0; i < 3; i++)
                check[i].clear();
        }
    }
    cout << res << '\n';

    return 0;
}

