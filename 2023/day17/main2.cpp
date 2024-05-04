#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> grid;
vector<vector<vector<int>>> dist;

bool ok(int x, int y) {return 0 <= x && x < n && 0 <= y && y < m;}

class Path {
    public:
    int x, y, dx, dy, weight, cnt;
    Path(int _x, int _y, int _dx, int _dy, int _w, int _cnt) {
        x =_x; y = _y; dx = _dx; dy = _dy;
        weight = _w; cnt = _cnt;
    }
    friend bool operator < (const Path &a, const Path &b) {
        if (a.weight == b.weight) return a.cnt > b.cnt;
        return a.weight > b.weight;
    }
    void process();
};


priority_queue<Path> pq;

void Path::process()
{
    if (x*y && weight > dist[x][y][cnt]) return;
    dist[x][y][cnt] = weight;
    // if (dx == 0 && dy == 1) dir[x-dx][y-dy] = '>';
    // else if (dx == 0 && dy == -1) dir[x-dx][y-dy] = '<';
    // else if (dx == 1 && dy == 0) dir[x-dx][y-dy] = 'v';
    // else if (dx == -1 && dy == 0) dir[x-dx][y-dy] = '^';
    int old, neww;
    if (ok(x+dx, y+dy) && cnt < 3) { // go straight
        old = dist[x+dx][y+dy][cnt+1]; neww = weight+grid[x+dx][y+dy];
        if (neww < old) pq.push(Path(x+dx, y+dy, dx, dy, neww, cnt+1));
    }
    if (ok(x-dy, y-dx)) { // turn left
        old = dist[x-dy][y-dx][0]; neww=weight+grid[x-dy][y-dx];
        if (neww < old) pq.push(Path(x-dy, y-dx, -dy, -dx, neww, 0));
    }
    if (ok(x+dy, y+dx)) { // turn right
        old = dist[x+dy][y+dx][0]; neww=weight+grid[x+dy][y+dx];
        if (neww < old) pq.push(Path(x+dy, y+dx, dy, dx, neww, 0));
    }
}

namespace part1
{
    void solve() // custom dijkstra
    {
        dist = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(4, 1e4)));
        pq.emplace(0, 0, 0, 1, 0, 0);
        dist[0][0][0] = 0;
        while (!pq.empty())
        {
            Path p = pq.top(); 
            pq.pop();
            p.process(); 
        }
        freopen("output.txt", "w", stdout);
            for (int i = 0; i < n; i++) {for (int j = 0; j < m; j++) {for (int k = 0; k < 3; k++)
                cout << (dist[i][j][k] == 1e4?".":to_string(dist[i][j][k])) << '|';
                cout << "\t\t";}
            cout << endl;
            }
            cout << endl;
        cout << dist[n-1][m-1][0] << ' ' << dist[n-1][m-1][1] << ' ' << dist[n-1][m-1][2] << ' ' << dist[n-1][m-1][3] << '\n';
        cout << *min_element(dist[n-1][m-1].begin(), dist[n-1][m-1].end()) << '\n';
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