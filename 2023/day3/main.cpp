#include <bits/stdc++.h>
using namespace std;

const int maxn = 153;
const int di[] = {0, 0, 1, -1, -1, -1, 1, 1};
const int dj[] = {-1, 1, 0, 0, -1, 1, -1, 1};

vector<string> grid;
int r, c;
long long res = 0;


namespace part1
{
    bool is_symbol(int i, int j)
    {
        return 0 <= i && i < r && 0 <= j && j < c && (grid[i][j] != '.') && (!isdigit(grid[i][j]));
    }

    void process_number(int x, int y) // (x, y) is the first digit from left to right of number
    {
        string s;
        bool ok = false;
        for (int j = y; j < c && isdigit(grid[x][j]); j++)
        {
            for (int k = 0; k < 8 && !ok; k++) ok |= is_symbol(x+di[k], j+dj[k]);
            s += grid[x][j];
            grid[x][j] = '.';
        }
        if (ok) res += stoi(s);
    }

    void solve()
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) 
                if (isdigit(grid[i][j])) process_number(i, j);
        cout << res << '\n';
    }
}

namespace part2
{
    int val[maxn][maxn];
    vector<pair<int, int>> gear_pos;
    bool is_gear(int i, int j)
    {return 0 <= i && i < r && 0 <= j && j < c && ((grid[i][j] == '*') || (grid[i][j] == 'A'));}

    void process_number(int x, int y) // (x, y) is the first digit from left to right of number
    {
        string s;
        int j, num;
        for (j = y; j < c && isdigit(grid[x][j]); j++)
        {
            for (int k = 0, ni, nj; k < 8; k++) 
            {
                ni = x+di[k], nj = j+dj[k];
                if (!(is_gear(ni, nj) && grid[ni][nj] != 'A')) continue;
                gear_pos.emplace_back(ni, nj);
                grid[ni][nj] = 'A'; // 'A' is marked gears so that there's no dupes
            }
            s += grid[x][j];
            grid[x][j] = '.';
        }
        j--; num = stoi(s);
        do val[x][j] = num;
        while (j-- > y);
    }

    void process_gear(int i, int j)
    {
        set<int> nums;
        for (int k = 0, ni, nj; k < 8; k++)
        {
            ni = i+di[k]; nj = j+dj[k]; if (ni < 0 || ni >= r || nj < 0 || nj >= c) continue;
            if (val[ni][nj]) nums.insert(val[ni][nj]);
        }
        if (nums.size() == 2) res += *nums.begin() * (*--nums.end());
    }

    void solve()
    {
        memset(val, 0, sizeof(val));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) 
                if (isdigit(grid[i][j])) process_number(i, j);
        // for (int i = 0; i < r; i++)
        // {
        //     for (int j = 0; j < c; j++) cout << val[i][j] << '\t';
        //     cout << '\n';
        // }
        for (int i = 0; i < gear_pos.size(); i++) 
            process_gear(gear_pos[i].first, gear_pos[i].second);
        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    string line;
    while (cin >> line)
    {
        if (line == "end") break;
        grid.push_back(line);
    }
    r = grid.size(); c = grid[0].size();
    part2::solve();
    
    return 0;
}