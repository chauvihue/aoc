#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a;
long long res = 0;

bool check(vector<int> history)
{
    bool ok = false;
    for (int i = 0; i < history.size(); i++) ok |= history[i];
    return ok;
}

namespace part1
{
    int predict(vector<int> history)
    {
        int ans = 0;
        while (check(history))
        {
            for (int i = 0; i < history.size()-1; i++)
                history[i] = history[i+1] - history[i];
            ans += history.back();
            history.pop_back();
        }
        return ans;
    }

    void solve()
    {
        for (int i = 0; i < a.size(); i++) res += predict(a[i]);
        cout << res << '\n';
    }
}

namespace part2
{
    int predict(vector<int> history)
    {
        int ans = 0; int prod = 1;
        while (check(history))
        {
            ans += prod*history[0];
            for (int i = 0; i < history.size()-1; i++)
                history[i] = history[i+1] - history[i];
            prod *= -1;
            history.pop_back();
        }
        return ans;
    }

    void solve()
    {
        for (int i = 0; i < a.size(); i++) res += predict(a[i]);
        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line; int num;
    while(getline(cin, line))
    {
        stringstream ss(line);
        a.push_back(vector<int>());
        while (ss >> num) a.back().push_back(num);
    }
    part1::solve();
    
    return 0;
}