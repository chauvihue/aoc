#include <bits/stdc++.h>
#define r first
#define c second
using namespace std;
using pii = pair<int, int>;

const string reff = "|-LJ7F";
const int dr[] = {-1,   0,  -1, -1, 1,  1};
const int dc[] = {0,    1,  1,  -1, -1, 1};
const string directions = "LRUD";
const int dirx[] = {0,  0,  -1, 1};
const int diry[] = {-1, 1,  0,  0};
const string walls = "|LJ"; 
// instead of L and J, we could use F and 7, it should work the same

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
    queue<pii> q;
    pii src;
    void flood(int x, int y, int dx, int dy) // flood from grid[x-dx][y-dy] --> grid[x][y]
    {
        if (!(e(x, y) && e(x-dx, y-dy))) return;
        int k = reff.find(grid[x][y]);
        if (k == string::npos || (dx != -dr[k] && dy != -dc[k])) return;
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
        src = find_start();
        dist[src.r][src.c] = 0;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) if (!(i*j)) flood(src.r+i, src.c+j, i, j);
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
    queue<pii> q;
    vector<string> dir;
    vector<vector<bool>> isloop;
    pii src, point1 = {-1, -1}, point2 = {-1, -1};
    bool found = false;
    char get_dir(int dx, int dy)
    {
        pii delta = {dx, dy};
        if (delta == make_pair(1, 0)) return 'U';
        else if (delta == make_pair(-1, 0)) return 'D';
        else if (delta == make_pair(0, 1)) return 'L';
        else if (delta == make_pair(0, -1)) return 'R';
        assert(false);
        return '!';
    }
    pii get_delta(char chr)
    {
        int k = directions.find(chr); assert(k != string::npos);
        return {dirx[k], diry[k]};
    }
    void trace(int x, int y) // trace from (x, y) to S
    {
        while (x != src.r || y != src.c)
        {
            isloop[x][y] = true;
            pii delta = get_delta(dir[x][y]);
            x += delta.r; y += delta.c;
        }
    }
    void flood(int x, int y, int dx, int dy) // flood from grid[x-dx][y-dy] --> grid[x][y]
    {
        if (!(e(x, y) && e(x-dx, y-dy))) return;
        int k = reff.find(grid[x][y]);
        if (k == string::npos || (dx != -dr[k] && dy != -dc[k])) return;
        if (dir[x][y] != '.') // either parent of pipe OR connecting to 2 ends of loop
        {
            // if its a parent, the direction of (x, y) should be pointing to (x-dx, y-dy)
            if (get_delta(dir[x-dx][y-dy]) == make_pair(dx, dy)) return;
            // else the loop is complete!
            point1 = {x, y}; point2 = {x-dx, y-dy}; 
            found = true;
            return;
        }
        // the directions are to trace from where the 2 ends of the loop connects -> point S
        dir[x][y] = get_dir(dx, dy);
        q.emplace(x, y);

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
    void remark_src(int dx, int dy)
    {
        isloop[src.r][src.c] = true;
        if (!dy) grid[src.r][src.c] = '|';
        else if (!dx) grid[src.r][src.c] = '-';
        for (int k = 2; k < 6; k++) if (dr[k] == dx && dc[k] == dy)
        {
            grid[src.r][src.c] = reff[k];
            break;
        }
    }
    void raytracing() // use raytracing to locate interior points
    {
        for (int i = 0, cnt; i < n; i++)
        {
            cnt = 0;
            for (int j = m-1; j >= 0; j--)
                if (isloop[i][j] && walls.find(grid[i][j]) != string::npos) cnt++;
                else if (cnt&1 && !isloop[i][j]) res++;
        }
    }
    void solve()
    {
        // same process as part1 but with some changes
        dir = vector<string>(n, string(m, '.'));
        isloop = vector<vector<bool>>(n, vector<bool>(m, false));
        src = find_start();
        int dx, dy;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) if (!(i*j) && (i+j) && e(src.r+i, src.c+j)) 
            {
                flood(src.r+i, src.c+j, i, j);
                if (dir[src.r+i][src.c+j] != '.') // this is to mark S as a specific type of pipe
                    i? dx = i : (j?dy = j:0);
            }
        // mark start point as a specific pipe
        while (!q.empty() && !found)
        {
            int i = q.front().r, j = q.front().c; q.pop();
            process_pipe(i, j);
        }
        // for (int i = 0; i < n; i++) cout << dir[i] << '\n';
        trace(point1.r, point1.c); trace(point2.r, point2.c);// trace to find and mark the pipes of the main loop
        remark_src(dx, dy);
        // for (int i = 0; i < n; i++) cout << grid[i] << '\n'; cout << '\n';
        // for (int i = 0; i < n; i++) cout << dir[i] << '\n'; cout << '\n';
        // cout << point1.r << ", " << point1.c << '\t' << point2.r << ", " << point2.c << '\n';
        // for (int i = 0; i < n; i++) {for (int j = 0; j < m; j++) cout << (isloop[i][j]?'1':'.') << ' '; cout << '\n';}
        /*
            we treat the main loop as a polygon (see ex1.png)
            use raytracing to check whether or not a point is inside a polygon or not!
            (from every row, shoot a ray from right to left, if it intersects with the polygon
            an odd amount of points before it hits a point -> the point is in the interior of the polygon)
        */
        raytracing();

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
    freopen("output.txt", "w", stdout);
    part2::solve();
    
    return 0;
}