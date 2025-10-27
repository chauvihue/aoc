#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using mapT = map<char, set<pii>>;

const int maxn = 53;

int n, m, res = 0;
vector<string> grid;
mapT p;

void parse() {
    n = grid.size(); m = grid[0].size();
    for (int i = 0, pos = -1; i < n; i++) {
        pos = grid[i].find_first_not_of('.');
        while (pos < m && pos != string::npos) {
            p[grid[i][pos]].insert({i, pos});
            pos = grid[i].find_first_not_of('.', pos+1);
        }
    }
}

namespace part1 {
    vector<bitset<maxn>> isanti;

    void process(pii a, pii b) {
        int dx = a.first-b.first, dy = a.second-b.second;
        int p1x = a.first+dx, p1y = a.second+dy;
        int p2x = b.first-dx, p2y = b.second-dy;
        if (0 <= p1x && p1x < n && 0 <= p1y && p1y < m) isanti[p1x][p1y] = true;
        if (0 <= p2x && p2x < n && 0 <= p2y && p2y < m) isanti[p2x][p2y] = true;
    }

    void solve() {
        isanti = vector<bitset<maxn>> (n, bitset<maxn>(0));
        for (mapT::iterator itr1 = p.begin(); itr1 != p.end(); itr1++) {
            char chr = itr1->first; set<pii> *st = &itr1->second;
            for (set<pii>::iterator itr2 = st->begin(); itr2 != st->end(); itr2++) 
                for (set<pii>::iterator itr3 = itr2; ++itr3 != st->end(); ) 
                    process(*itr2, *itr3);
        }
        for (int i = 0; i < n; i++) res += isanti[i].count();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (grid[i][j] != '.') cout << grid[i][j];
                else cout << (isanti[i][j]?'#':'.');
            cout << '\n';
        }  
        cout << res << '\n';
    }
}

namespace part2 {
    vector<bitset<maxn>> isanti;

    void process(pii a, pii b) {
        int dx = a.first-b.first, dy = a.second-b.second;
        int px = a.first, py = a.second;
        while (0 <= px && px < n && 0 <= py && py < m) {
            isanti[px][py] = true;
            px += dx; py += dy;
        }
        px = b.first; py = b.second;
        while (0 <= px && px < n && 0 <= py && py < m) {
            isanti[px][py] = true;
            px -= dx; py -= dy;
        }
    }

    void solve() {
        isanti = vector<bitset<maxn>> (n, bitset<maxn>(0));
        for (mapT::iterator itr1 = p.begin(); itr1 != p.end(); itr1++) {
            char chr = itr1->first; set<pii> *st = &itr1->second;
            for (set<pii>::iterator itr2 = st->begin(); itr2 != st->end(); itr2++) 
                for (set<pii>::iterator itr3 = itr2; ++itr3 != st->end(); ) 
                    process(*itr2, *itr3);
        }
        for (int i = 0; i < n; i++) res += isanti[i].count();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (grid[i][j] != '.') cout << grid[i][j];
                else cout << (isanti[i][j]?'#':'.');
            cout << '\n';
        }  
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (getline(cin, line)) grid.push_back(line);
    parse();
    part2::solve();

    return 0;
}