#include <bits/stdc++.h>
using namespace std;

const string reff[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
                        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

string s;
long long sum = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    while (cin >> s)
    {
        if (s == "end") break;
        int i = s.size(), j = -1, vali, valj;
        for (int k = 0; k < 19; k++)
        {
            string ss;
            //for (int pos = 0; pos < s.size(); pos++) cout << s.substr(pos, reff[k].size()) << '\n';
            for (int pos = 0; pos < s.size(); pos++) if (s.substr(pos, reff[k].size()) == reff[k] && i > pos)
            {
                i = pos;
                vali = k;
                break;
            }
            for (int pos = s.size()-1; pos >= 0; pos--) if (s.substr(pos, reff[k].size()) == reff[k] && j < pos)
            {
                j = pos;
                valj = k;
                break;
            }
        }
        //cout << i << ' ' << vali << ' ' << j << ' ' << valj << '\n';
        if (i < s.size() && j >= 0)
        {
            if (vali > 9) vali -= 9;
            if (valj > 9) valj -= 9;
            if (vali == 0) continue;
            sum += vali*10 + valj;
            cout << vali*10 + valj << '\n';
        }
    }
    cout << sum << '\n';
    
    return 0;
}