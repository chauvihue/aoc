#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
using pii = pair<int, int>;

const string BRED = "\x1b[1;41m";
const string BGREEN = "\x1b[1;102m";
const string RESET = "\x1b[0m";
const string reff = "^>v<";
const string displayreff = "0123";
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int n, m, res = 0;
pii src;
vector<string> grid;

namespace part1 {
    void walk (int x, int y, char dir='^') {
        if (grid[x][y] == '.') grid[x][y] = dir, res++;
        int newx = x+dx[reff.find(dir)], newy = y+dy[reff.find(dir)];
        if (newx < 0 || m <= newx || newy < 0 || n <= newy) return;
        if (grid[newx][newy] == '#') {
            dir = reff[(reff.find(dir)+1)%reff.size()];
            newx = x+dx[reff.find(dir)]; newy = y+dy[reff.find(dir)]; 
        } 
        walk(newx, newy, dir); 
        // return true;
    }

    void solve() {
        for (int i = 0; i < n; i++)
            if (grid[i].find('^') != string::npos) src = {i, grid[i].find('^')};
        grid[src.first][src.second] = '.';
        walk(src.first, src.second);
        for (int i = 0; i < n; i++) cout << grid[i] << endl;
        cerr << res << '\n';
    }
}

namespace part2 {
    vector<string> g;
    vector<vector<bitset<4>>> visited;
    queue<pii> q;
    pii loopsrc; char loopdir;

    bool walk(int x, int y, char dir='^', bool init=false) {
        int k = reff.find(dir);
        if (g[x][y] == '.') {
            g[x][y] = dir;
            if (init) q.emplace(x, y);
        }
        if (visited[x][y][k]) {loopsrc = {x, y}; loopdir = reff[k]; return false;}
        visited[x][y][k] = true;
        int newx = x+dx[k], newy = y+dy[k];
        if (newx < 0 || m <= newx || newy < 0 || n <= newy) return true;
        while (g[newx][newy] == '#') {
            k = (k+1)%reff.size();
            dir = reff[k];
            newx = x+dx[k]; newy = y+dy[k]; 
        } 
        return walk(newx, newy, dir, init); 
        // return true;
    }
       
    void display(int wait=0) {
        string print; // clear screen
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (i == loopsrc.first && j == loopsrc.second) print += BRED + reff[g[i][j]-'0'] + RESET;
                else if (displayreff.find(g[i][j]) != string::npos) print += BGREEN + reff[g[i][j]-'0'] + RESET;
                else print += g[i][j];
            print += '\n';
        }
        system("cls");
        cout << print << endl;
        // if (wait != 100) cout << BRED << "COMPLETED CYCLE #" << res << RESET << endl;
        if (wait > 0) Sleep(wait);
    }

    void trace() {
        int x = loopsrc.first, y = loopsrc.second, newx, newy, k = reff.find(loopdir);
        char dir = loopdir;
        g[x][y] = displayreff[k];
        do {
            newx = x+dx[k]; newy = y+dy[k];
            while (g[newx][newy] == '#') {
                k = (k+1)%reff.size();
                dir = reff[k];
                newx = x+dx[k]; newy = y+dy[k]; 
            } 
            x = newx; y = newy;
            g[x][y] = displayreff[k];
            display();
        } while (x != loopsrc.first || y != loopsrc.second || dir != loopdir);
    }
    
    void solve() {
        for (int i = 0; i < n; i++)
            if (grid[i].find('^') != string::npos) src = {i, grid[i].find('^')};
        grid[src.first][src.second] = '.';
        g = grid; visited = vector<vector<bitset<4>>>(n, vector<bitset<4>>(m, 0));;
        walk(src.first, src.second, '^', true);
        while(!q.empty()) {
            int i = q.front().first, j = q.front().second; q.pop();
            if (i == src.first && j == src.second) continue;
            g = grid;
            visited = vector<vector<bitset<4>>>(n, vector<bitset<4>>(m, 0));
            g[i][j] = '#';
            if (walk(src.first, src.second)) continue; 
            res++;
            trace();
            display(3000);
        }
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while (cin >> line) grid.push_back(line);
    n = grid.size(); m = grid[0].size();
    part2::solve();

    return 0;
}