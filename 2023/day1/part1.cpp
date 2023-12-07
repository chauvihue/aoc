#include <bits/stdc++.h>
using namespace std;

string s;
long long sum = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);
    while (cin >> s)
    {
        if (s == "end") break;
        int i, j;
        for (i = 0; i < s.size(); i++) if ('0' <= s[i] && s[i] <= '9') break;
        for (j = s.size()-1; j >= 0; j--) if ('0' <= s[j] && s[j] <= '9') break;
        if (i < s.size() && j >= 0) sum += (s[i]-'0')*10 + (s[j]-'0');
    }
    cout << sum << '\n';
    
    return 0;
}