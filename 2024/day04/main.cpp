#include <bits/stdc++.h>
using namespace std;


int res = 0;
vector<string> grid;


namespace part1 {
    const string reff = "XMAS";
    const int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    const int dy[] = {0, 0, -1, 1, -1, 1, 1, -1};
    bool e(int x, int y) {return 0 <= x && x < grid.size() && 0 <= y && y < grid[0].size();}
    bool check(int x, int y, int k) {
        bool ans = true;
        int i;
        for (i = 0; i < 4 && e(x, y); i++) {
            ans &= grid[x][y] == reff[i];
            x += dx[k]; y += dy[k];
        }
        return ans && i == 4;
    }

    void solve() {
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++) if (grid[i][j] == 'X')
                for (int k = 0; k < 8; k++) if (check(i, j, k)) res++;
        cout << res << '\n';
    }
}

namespace part2 {
    bool check(int x, int y) {
        char l[2] = {grid[x-1][y-1], grid[x+1][y+1]}, r[2] = {grid[x-1][y+1], grid[x+1][y-1]};
        bool ans = (l[0]=='M'&&l[1]=='S') || (l[1]=='M'&&l[0]=='S');
        ans &= (r[0]=='M'&&r[1]=='S') || (r[1]=='M'&&r[0]=='S');
        return ans;
    }

    void solve() {
        for (int i = 1; i < grid.size()-1; i++)
            for (int j = 1; j < grid[i].size()-1; j++) if (grid[i][j] == 'A')
                if (check(i, j)) res++;
        cout << res << '\n';
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (getline(cin, line)) grid.push_back(line);
    part2::solve();

    return 0;
}