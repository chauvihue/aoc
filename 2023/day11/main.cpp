#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll = long long;

const int EXTRA_GALAXIES = 1e6;

vector<string> grid;
vector<pair<int, int>> pos;
int n, m;
ll res = 0;

void find_galaxies()
{
    for (int i = 0, j; i < n; i++) 
    {
        j = grid[i].find('#');
        while (j != string::npos)
        {
            pos.emplace_back(i, j);
            j = grid[i].find('#', j+1);
        }
    }
}

namespace part1
{
    void expand_universe()
    {
        vector<bool> row(n, false), col(m, false); // check if row or collumns have planet
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            if (grid[i][j] == '#') row[i] = col[j] = true;

        // expand rowss
        for (int i = 0, delta = 0; i < n; i++) if (!row[i])
        {
            grid.insert(grid.begin()+i+delta, string(m, '.'));
            delta++;
        }
        n = grid.size();

        // expand collumns
        for (int j = 0, delta = 0; j < m; j++) if (!col[j])
        {
            for (int i = 0; i < n; i++) grid[i].insert(j+delta, ".");
            delta++;
        }
        m = grid[0].size();
    }

    void solve()
    {
        expand_universe();
        find_galaxies();
        for (int i = 0; i < pos.size(); i++) for (int j = i+1; j < pos.size(); j++)
            res += abs(pos[i].x - pos[j].x) + abs(pos[i].y - pos[j].y);

        cout << res << '\n';
    }   
}

namespace part2
{
    vector<ll> pre_row, pre_col;
    void expand_universe()
    {
        vector<bool> row(n, false), col(m, false); // check if row or collumns have planet
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            if (grid[i][j] == '#') row[i] = col[j] = true;

        // instead of inserting in characters/strings, we use prefix sum
        // to sum up the extra 1 000 000 galaxies
        pre_row[0] = pre_col[0] = 0;
        // if this row is empty, the space in between is EXTRA_GALAXIES, else 1
        for (int i = 1; i < n; i++) pre_row[i] = pre_row[i-1] + (row[i]?1:EXTRA_GALAXIES);
        // same goes with collumns
        for (int j = 1; j < m; j++) pre_col[j] = pre_col[j-1] + (col[j]?1:EXTRA_GALAXIES);
    }

    ll path_length(int x1, int y1, int x2, int y2)
    {
        /*
            The lengths of these 2 paths are the same 
                        (regardless dupes):

                        ...#            #...
                        ....    ==      ....
                        #...            ...#
                        (1)             (2)

            we transform path 1 to path 2 for easy calculations
        */
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        return pre_col[y2] - (!y1?0:pre_col[y1]) + pre_row[x2] - (!x1?0:pre_row[x1]);
    }

    void solve()
    {
        pre_row = vector<ll>(n, 0); 
        pre_col = vector<ll>(m, 0); 
        expand_universe();
        find_galaxies();
        for (int i = 0, t; i < pos.size(); i++) for (int j = i+1; j < pos.size(); j++)
            res += path_length(pos[i].x, pos[i].y, pos[j].x, pos[j].y); 
        
        cout << res << '\n';
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    while (getline(cin, line)) grid.push_back(line);
    n = grid.size(); m = grid[0].size();
    part2::solve();
    
    return 0;
}