#include <bits/stdc++.h>
using namespace std;
using vvbs = vector<vector<bitset<4>>>;

int n, m, res = 0;
vector<string> grid;
vvbs state;

bool e(int x, int y) {return 0 <= x && x < n && 0 <= y && y < m;}

class Beam {
    int x, y, dx, dy;
    public:
    Beam(int _x, int _y, int _dx, int _dy) {
        x = _x; y = _y; dx = _dx; dy = _dy;
    }
    void process(); // process beam
};
queue<Beam> q;

void Beam::process() { // process beam
        // state[x][y] = {left, right, up, down}
        if (!e(x, y) || (dy==-1 && state[x][y][0]) || (dy==1 && state[x][y][1])
                    || (dx==-1 && state[x][y][2]) || (dx==1 && state[x][y][3])) return;
        if (dy) state[x][y][dy==1] = true;
        else if (dx) state[x][y][2 + (dx==1)] = true;
        if (grid[x][y] == '.' || (dx && grid[x][y] == '|') || (dy && grid[x][y] == '-')) // continue with current dir
            q.emplace(x+dx, y+dy, dx, dy);
        else if (grid[x][y] == '|' || grid[x][y] == '-') { // create 2 beams on the side 
            if (grid[x][y] == '|') {q.emplace(x-1, y, -1, 0); q.emplace(x+1, y, 1, 0);}
            else {q.emplace(x, y-1, 0, -1); q.emplace(x, y+1, 0, 1);}
        } else { // reflect off of '/' and '\'
            if (grid[x][y] == '\\') q.emplace(x+dy, y+dx, dy, dx);
            else q.emplace(x-dy, y-dx, -dy, -dx);
        }
    }


namespace part1
{
    void solve()
    {
        state = vvbs(n, vector<bitset<4>>(m, 0));
        q.emplace(0, 0, 0, 1);
        while (!q.empty()) {
            Beam b = q.front(); q.pop();
            b.process();
        }
        // for (int i = 0; i < n; i++) {for (int j = 0; j < m; j++)
        //     cout << (state[i][j].to_ulong()?'#':'.'); cout << endl;
        // }
        // cout << endl;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            res += state[i][j].to_ullong()>0;
        cout << res << '\n';
    }
} 

namespace part2
{
    int simulate(int x, int y, int dx, int dy)
    {
        int ans = 0;
        state = vvbs(n, vector<bitset<4>>(m, 0));
        q.emplace(x, y, dx, dy);
        while (!q.empty()) {
            Beam b = q.front(); q.pop();
            b.process();
        }
        // for (int i = 0; i < n; i++) {for (int j = 0; j < m; j++)
        //     cout << (state[i][j].to_ulong()?'#':'.'); cout << endl;
        // }
        // cout << endl;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            ans += state[i][j].to_ullong()>0;
        return ans;
    }

    void solve()
    {
        for (int i = 0; i < n; i++) res = max(res, max(simulate(i, 0, 0, 1), simulate(i, m-1, 0, -1)));
        for (int j = 0; j < m; j++) res = max(res, max(simulate(0, j, 1, 0), simulate(n-1, j, -1, 0)));
        
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