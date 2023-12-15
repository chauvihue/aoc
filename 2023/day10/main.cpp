#include <bits/stdc++.h>
#define r first
#define c second
using namespace std;
using pii = pair<int, int>;

const string reff = "|-LJ7F";
const int dr[] = {-1,   0,  -1, -1, 1,  1};
const int dc[] = {0,    1,  1,  -1, -1, 1};

vector<string> grid;
int n, m, res = 0;

bool e(int x, int y)
{return 0 <= x && x < n && 0 <= y && y < m && grid[x][y] != '.';}

pii find_start()
{
    for (int i = 0, pos; i < n; i++)
    {
        pos = grid[i].find('S');
        if (pos != string::npos) return {i, pos};
    }
    return {-1, -1};
}



namespace part1
{
    vector<vector<int>> dist;
    queue<pair<int, int>> q;
    void flood(int x, int y, int dx, int dy) // flood from grid[x-dx][y-dy] --> grid[x][y]
    {
        if (!(e(x, y) && e(x-dx, y-dy))) return;
        int k = reff.find(grid[x][y]);
        if (k == string::npos && dx != -dr[k] && dy != -dc[k]) return;
        if (dist[x][y] == 1e9) q.emplace(x, y);
        dist[x][y] = min(dist[x][y], dist[x-dx][y-dy]+1);
    }
    void process_pipe(int x, int y)
    {
        if (grid[x][y] == '|') 
            for (int d = -1; d <= 1; d += 2) flood(x+d, y, d, 0);
        else if (grid[x][y] == '-')
            for (int d = -1; d <= 1; d += 2) flood(x, y+d, 0, d);
        else {
            int k = reff.find(grid[x][y]); if (k == string::npos) return;
            flood(x+dr[k], y, dr[k], 0);
            flood(x, y+dc[k], 0, dc[k]);
        }
    }
    void solve()
    {
        dist = vector<vector<int>>(n, vector<int>(m, 1e9));
        pii pos = find_start();
        dist[pos.r][pos.c] = 0;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) if (!(i*j)) flood(pos.r+i, pos.c+j, i, j);
        while (!q.empty())
        {
            int i = q.front().r, j = q.front().c; q.pop();
            process_pipe(i, j);
            res = max(res, dist[i][j]);
        }

        cout << res << '\n';
    }
};

namespace part2
{
    queue<pair<int, int>> q;
    vector<string> dir;
    vector<vector<int>> pipe_pos;
    void trace()
    {
        
    }
    void flood(int x, int y, int dx, int dy) // flood from grid[x-dx][y-dy] --> grid[x][y]
    {
        if (!(e(x, y) && e(x-dx, y-dy))) return;
        int k = reff.find(grid[x][y]);
        if (k == string::npos && dx != -dr[k] && dy != -dc[k]) return;
        // TODO: MARK DIRECTIONS
    }
    void process_pipe(int x, int y)
    {
        if (grid[x][y] == '|') 
            for (int d = -1; d <= 1; d += 2) flood(x+d, y, d, 0);
        else if (grid[x][y] == '-')
            for (int d = -1; d <= 1; d += 2) flood(x, y+d, 0, d);
        else {
            int k = reff.find(grid[x][y]); if (k == string::npos) return;
            flood(x+dr[k], y, dr[k], 0);
            flood(x, y+dc[k], 0, dc[k]);
        }
    }
    void solve()
    {
        // same process as part1 but with some changes
        dir = vector<string>(n, string(m, '.'));
        pipe_pos = vector<vector<int>>(n);
        pii pos = find_start();
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) if (!(i*j)) flood(pos.r+i, pos.c+j, i, j);
        while (!q.empty())
        {
            int i = q.front().r, j = q.front().c; q.pop();
            process_pipe(i, j);
        }
        trace(); // trace to find and mark the boundaries main loop
        /*
            The idea is that for every row, there must be an even amount of
            boundary pipes (pipes that adjacent to no more than 1 other pipe) of the main loop
            --> find those pipes 
        */

    }
} 


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    while (cin >> line) grid.push_back(line);
    n = grid.size(); m = grid[0].size();
    part1::solve();
    
    return 0;
}