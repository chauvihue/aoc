#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxN = 1e4;

vector<vector<int>> graph;
int l[maxN][maxN], u[maxN][maxN], r[maxN][maxN], d[maxN][maxN];
int n, m;
ll res = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (true)
    {
        vector<int> curline;
        cin >> s;
        if (s == "-1")
            break;
        for (int i = 0; i < s.size(); i++)
            curline.push_back(s[i]-'0');
        graph.emplace_back(curline);
    }
    n = graph.size();
    m = graph[0].size();

    for (int i = 0; i < n; i++)
    {
        l[i][0] = -1;
        for (int j = 1; j < m; j++)
            l[i][j] = max(l[i][j-1], graph[i][j-1]);
    }
    for (int i = 0; i < n; i++)
    {
        u[i][0] = -1;
        for (int j = 1; j < m; j++)
            u[i][j] = max(u[i][j-1], graph[j-1][i]);
    }
    for (int i = 0; i < n; i++)
    {
        r[i][m-1] = -1;
        for (int j = m-2; j >= 0; j--)
            r[i][j] = max(r[i][j+1], graph[i][j+1]);
    }
    for (int i = 0; i < n; i++)
    {
        d[i][m-1] = -1;
        for (int j = m-2; j >= 0; j--)
            d[i][j] = max(d[i][j+1], graph[j+1][i]);
    }
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cerr << l[i][j] << '|' << u[i][j] << '|' << d[i][j] << '|' << d[i][j] << "\t\t";
        cerr << '\n';
    }*/
    for (int i = 0, mi; i < graph.size(); i++)
        for (int j = 0; j < graph[i].size(); j++)
        {
            mi = min(l[i][j], min(u[j][i], min(r[i][j], d[j][i])));
            //cerr << '(' << i << ", " << j << ")\n";
            //cerr << mi << '\t' << l[i][j] << ' ' << u[i][j] << ' ' << r[i][j] << ' ' << d[i][j] << '\n';
            if (mi < graph[i][j])
            {
                res++;
                //cerr << "!!!\n";
            }
        }
    cout << res << '\n';

    return 0;
}
