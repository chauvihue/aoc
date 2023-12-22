#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
int n, m, res = 0;

namespace part1
{
    int tilt_col(int j)
    {
        int sum = 0;
        for (int i = 0, val = n; i < n; i++)
            if (grid[i][j] == '#') val = n-i-1;
            else if (grid[i][j] == 'O') {sum += val; val--;}
        return sum;
    }

    void solve()
    {
        for (int j = 0; j < m; j++) res += tilt_col(j);

        cout << res << '\n';
    }
}

namespace part2
{
    const int num_cycle = 1;
    vector<vector<int>> rock, block; // 'O' pos in col j are in rock[j] , '#' pos in col j are in block[j] 
    void init() { // initialize rock and block vectors
        rock = block = vector<vector<int>>(m);
        for (int j = 0; j < m; j++)
        {
            for (int i = 0; i < n; i++)
                if (grid[i][j] == 'O') rock[j].push_back(i);
                else if (grid[i][j] == '#') block[j].push_back(i);
            block[j].push_back(n); // extra rock for buffer
        }
        // for (int i = 0; i < n; i++)
        // {
        //     cerr << i << '\t';
        //     for (auto a : rock[i]) cerr << a << ' '; cerr << '\t';
        //     for (auto a : block[i]) cerr << a << ' '; cerr << '\n';
        // }
    }
    void tilt_north() { // tilt the grid north and update rock
        for (int j = 0, k = 0; j < m; j++) {
            for (int i = 0, cur = -1; i < rock[j].size(); i++) {
                if (rock[j][i] > block[j][k]) {
                    k++; // there's a buffer rock so its a-ok
                    cur = block[j][k]+1;
                } else cur++;
                rock[j][i] = n-cur;
            }
        }
    }
    void rotate_right() { // rotate the grid 90 degree clockwise and update rock and block
        vector<vector<int>> newr, newb(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                newr[i].push_back(rock[j][i]);
            }
        swap(n, m);
    }
    void cycle_tilt() { // perform a cycle of tilts, return last positions value
        for (int _ = 0; _ < 4; _++) {rotate_right(); tilt_north();}
    }
    int calc_value() { // calculate value of 'O'

    }
    void solve()
    {
        init();
        tilt_north();
        for (int i = 0; i < num_cycle; i++) cycle_tilt();
        res = calc_value();

        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    while (cin >> line) grid.push_back(line);
    n = grid.size(); m = grid[0].size();
    part2::solve();
    
    return 0;
}