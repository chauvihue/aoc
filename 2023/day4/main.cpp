#include <bits/stdc++.h>
#define win first
#define num second
using namespace std;

vector<pair<vector<int>, vector<int>>> cards;

string line;
int n, m, res = 0;

int process_card(vector<int> a, vector<int> b)
{
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int cnt = 0;
    for (int i = 0, j = 0; j < m; j++) // 2 pointers
    {
        while (i+1 < n && a[i+1] <= b[j]) i++;
        cnt += a[i] == b[j];
    }
    return cnt;
}

namespace part1
{
    void solve()
    {
        for (int i = 0, cnt; i < cards.size(); i++)
        {
            cnt = process_card(cards[i].win, cards[i].num);
            if (cnt) res += 1<<(cnt-1);
        }
        cout << res << '\n';
    }
} 

namespace part2
{
    void solve()
    {
        int copy[cards.size()+3];
        memset(copy, 0, sizeof(copy));
        for (int i = 0, cnt; i < cards.size(); i++)
        {
            copy[i]++;
            cnt = process_card(cards[i].win, cards[i].num);
            for (int j = i+1; j <= i+cnt; j++) copy[j] += copy[i];
            res += copy[i];
        }
        cout << res << '\n';
    }
} 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    while (getline(cin, line))
    {
        stringstream ss(line);
        string str; int num;
        ss >> str >> num >> str;
        bool ok = false;
        cards.emplace_back(vector<int>(), vector<int>());
        while (ss >> str)
        {
            if (str == "|") {ok = true; continue;}
            num = stoi(str);
            if (!ok) cards.back().win.push_back(num);
            else cards.back().num.push_back(num);
        }
    }
    n = cards[0].win.size(); m = cards[0].num.size();
    part2::solve();
    
    return 0;
}