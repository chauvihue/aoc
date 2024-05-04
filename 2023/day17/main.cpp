#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> grid, dist;
vector<string> dir;

bool ok(int x, int y) {return 0 <= x && x < n && 0 <= y && y < m;}

class Path {
    int x, y, dx, dy, weight, cnt;
    public:
    Path(int _x, int _y, int _dx, int _dy, int _w, int _cnt) {
        x =_x; y = _y; dx = _dx; dy = _dy;
        weight = _w; cnt = _cnt;
    }
    friend bool operator < (const Path &a, const Path &b) {
        if (a.weight == b.weight) return a.cnt > b.cnt;
        return a.weight > b.weight;
    }
    void process(priority_queue<Path> &pq)
    {
        if (dist[n-1][m-1] < 1e9) return;
        dist[x][y] = min(dist[x][y], weight);
        // if (dx == 0 && dy == 1) dir[x-dx][y-dy] = '>';
        // else if (dx == 0 && dy == -1) dir[x-dx][y-dy] = '<';
        // else if (dx == 1 && dy == 0) dir[x-dx][y-dy] = 'v';
        // else if (dx == -1 && dy == 0) dir[x-dx][y-dy] = '^';
        if (ok(x+dx, y+dy) && cnt < 3) // go straight
            pq.emplace(x+dx, y+dy, dx, dy, weight+grid[x+dx][y+dy], cnt+1);
        if (ok(x-dy, y-dx)) // turn left
            pq.emplace(x-dy, y-dx, -dy, -dx, weight+grid[x-dy][y-dx], 0);
        if (ok(x+dy, y+dx)) // turn right
            pq.emplace(x+dy, y+dx, dy, dx, weight+grid[x+dy][y+dx], 0);
    }
};

priority_queue<Path> pq;

namespace part1
{
    void solve() // custom dijkstra
    {
        dist = vector<vector<int>>(n, vector<int>(m, 1e9));
        dir = vector<string>(n, string(m, '.'));
        pq.emplace(0, 0, 0, 1, 0, 0);
        dist[0][0] = 0;
        while (!pq.empty() && dist[n-1][m-1] == 1e9)
        {
            Path p = pq.top(); pq.pop();
            p.process(pq); 
            // for (int i = 0; i < n; i++) {for (int j = 0; j < m; j++)
            //     cout << (dist[i][j] == 1e9?".":to_string(dist[i][j])) << '\t';
            //     cout << endl;
            // }
            // cout << endl;
        }
        // for (int i = 0; i < n; i++) cout << dir[i] << '\n';
        cout << dist[n-1][m-1] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    while (cin >> line) {
        grid.push_back(vector<int>());
        for (int i = 0; i < line.size(); i++) grid.back().push_back(line[i]-'0');
    }
    n = grid.size(); m = grid[0].size();
    part1::solve();
    
    return 0;
}