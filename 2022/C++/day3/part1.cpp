#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s, half1, half2;
    ll res = 0;
    while (true)
    {
        map<char, bool> check1, check2;
        cin >> s;
        if (s == "-1")
            break;
        half1 = s.substr(0, s.size()/2);
        half2 = s.substr(s.size()/2, s.size()/2);
        for (int i = 0; i < half1.size(); i++)
            check1[half1[i]] = true;
        for (int i = 0; i < half2.size(); i++)
            check2[half2[i]] = true;
        for (char chr = 'a'; chr <= 'z'; chr++)
            if (check1[chr] && check1[chr] == check2[chr])
            {
                res += chr-'a'+1;
                //cerr << chr << "*\n";
                break;
            }
        for (char chr = 'A'; chr <= 'Z'; chr++)
            if (check1[chr] && check1[chr] == check2[chr])
            {
                res += chr-'A'+27;
                //cerr << chr << "*\n";
                break;
            }
    }
    cout << res << '\n';

    return 0;
}

