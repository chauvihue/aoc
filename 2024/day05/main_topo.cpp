#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

// # of ordering rules < 2e4, # of updates < 200
const int maxval = 100;

ll res = 0;

vector<pii> ord;
vector<vector<int>> a;

namespace part1 {
    bitset<maxval> rule[maxval]; 
    unordered_map<int, int> pos;

    void gen_rule(bitset<maxval> bs[]) {
        for (int i = 0; i < maxval; i++) bs[i] = 0;
        for (int i = 0, f, l; i < ord.size(); i++)
            bs[ord[i].first][ord[i].second] = true;
    }

    bool ok(vector<int> &vec, bitset<maxval> r[]) {
        pos.clear();
        bool ans = true;
        for (int i = 0; i < vec.size(); i++) pos[vec[i]] = i;
        for (int i = 0; i < vec.size() && ans; i++)
            for (int j = i-1; j >= 0 && ans; j--)
                ans &= r[vec[j]][vec[i]];
        return ans;
    }

    void solve() {
        gen_rule(rule);
        for (int i = 0; i < a.size(); i++) if (ok(a[i], rule)) 
            res += a[i][a[i].size()>>1];
        cout << res << '\n';
    }
} 

namespace part2 {
    bitset<maxval> rule[maxval]; 
    unordered_map<int, int> pos;
    vector<int> graph[maxval];
    int indeg[maxval];

    void rearrange(vector<int> &vec) {
        memset(indeg, 0, sizeof(indeg));
        for (int i = 0; i < vec.size(); i++) { 
            graph[vec[i]].clear();
            for (int j = 0; j < vec.size(); j++) if (rule[vec[i]][vec[j]]) {
                    graph[vec[i]].push_back(vec[j]);
                    indeg[vec[j]]++;
                }
        }
        queue<int> q;
        for (int i = 0; i < vec.size(); i++) 
            if (indeg[vec[i]] == 0) {q.push(vec[i]); break;}
        vec.clear();
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vec.push_back(u);
            for (int i = 0, v; i < graph[u].size(); i++) {
                v = graph[u][i];
                if (--indeg[v] == 0) q.push(v);
            }
        }
        for (auto ai : vec) cout << ai << ' '; cout << '\n';
    }

    void solve() {
        part1::gen_rule(rule);
        for (int i = 0; i < a.size(); i++) if (!part1::ok(a[i], rule)) {
            rearrange(a[i]);
            res += a[i][a[i].size()>>1];
        }
        cout << res << '\n';
    }
} 


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (cin >> line) {
        stringstream ss(line); char chr; int num;
        if (line.find('|') != string::npos) {
            ord.push_back(pii());
            ss >> ord.back().first >> chr >> ord.back().second;
        } else if (line.find(',') != string::npos) {
            a.push_back(vector<int>());
            ss >> num; a.back().push_back(num);
            while (ss >> chr >> num) a.back().push_back(num);
        }
    }
    part2::solve();

    return 0;
}