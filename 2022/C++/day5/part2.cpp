#include <bits/stdc++.h>
using namespace std;

const int maxN = 10;

vector<string> crates_raw;
stack<char> crates[maxN+1];
bool reading_crates = true, done_init = false;
int n = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (true)
    {
        getline(cin, s);
        if (s == "-1")
        {
            for (int i = 1; i <= n; i++)
                cout << crates[i].top();
            break;
        }
        reading_crates &= (s.find('[') != string::npos);
        if (reading_crates)
            crates_raw.push_back(s);
        else if (!done_init)
            {
                n = (crates_raw[0].size()-1)/4+1;
                while (!crates_raw.empty())
                {
                    s = crates_raw.back();
                    for (int i = 0; 1+4*i < s.size(); i++) if (s[1+4*i] != ' ')
                        crates[i+1].push(s[1+4*i]);
                    crates_raw.pop_back();
                }
                done_init = true;
                getline(cin, s);
            }
        else
        {
            int cnt, src, des;
            stringstream ss(s);
            ss >> s >> cnt >> s >> src >> s >> des;
            string moved_crates;
            while (cnt--)
            {
                moved_crates += crates[src].top();
                crates[src].pop();
            }
            for (int i = moved_crates.size()-1; i >= 0; i--)
                crates[des].push(moved_crates[i]);
        }
    }

    return 0;
}


