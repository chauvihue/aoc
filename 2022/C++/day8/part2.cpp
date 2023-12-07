#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxN = 1e3;

vector<vector<int>> graph;
int l[maxN][maxN], u[maxN][maxN], r[maxN][maxN], d[maxN][maxN];
int n;
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

    /*for (int i = 0; i < n; i++)
    {
        u[i][0] = {-1, 0};
        for (int j = 1; j < m; j++)
        {
            if (u[i][j-1].val < graph[j-1][i])
                u[i][j] = {graph[j-1][i], j-1};
            else
                u[i][j] = u[i][j-1];
        }
    }
    for (int i = 0; i < n; i++)
    {
        r[i][0] = {-1, 0};
        for (int j = m-2; j >= 0; j--)
        {
            if (r[i][j+1].val < graph[i][j+1])
                r[i][j] = {graph[i][j+1], j+1};
            else
                r[i][j] = r[i][j+1];
        }
    }
    for (int i = 0; i < n; i++)
    {
        d[i][0] = {-1, 0};
        for (int j = 1; j < m; j++)
        {
            if (d[i][j+1].val < graph[j+1][i])
                d[i][j] = {graph[j+1][i], j+1};
            else
                d[i][j] = d[i][j+1];
        }
    }*/

    /*for (int i = 0; i < n; i++)
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
    }*/
    for (int i = 1, l, r, u, d; i < n-1; i++)
        for (int j = 1; j < n-1; j++)
        {
            l = r = u = d = 0;
            for (int jj = j-1; jj >= 0; jj--)
            {
                l++;
                if (graph[i][jj] >= graph[i][j])
                    break;
            }
            for (int jj = j+1; jj < n; jj++)
            {
                r++;
                if (graph[i][jj] >= graph[i][j])
                    break;
            }
            for (int ii = i-1; ii >= 0; ii--)
            {
                u++;
                if (graph[ii][j] >= graph[i][j])
                    break;
            }
            for (int ii = i+1; ii < n; ii++)
            {
                d++;
                if (graph[ii][j] >= graph[i][j])
                    break;
            }
            /*for (int ii = i-1; ii >= 0 && graph[ii][j] < graph[i][j] && graph[i-1][j] < graph[i][j]; ii--)
                u++;
            for (int ii = i+1; ii < n && graph[ii][j] < graph[i][j] && graph[i+1][j] < graph[i][j]; ii++)
                d++;*/
            res = max(res, 1LL*l*r*u*d);
            //cerr << '(' << i << ", " << j << ")\t" << l << ' ' << r << ' ' << u << ' ' << d << '\n';
        }
    cout << res << '\n';

    return 0;
}

