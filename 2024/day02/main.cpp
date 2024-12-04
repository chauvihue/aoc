#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a;
int res = 0;

namespace part1 {
    bool ok(vector<int> &vec) {
        bool ans = vec[0] != vec[1] && abs(vec[0]-vec[1]) <= 3, isinc = vec[0] < vec[1];
        for (int i = 2; i < vec.size() && ans; i++)
            ans &= vec[i-1] != vec[i] && (vec[i-1]<vec[i] == isinc) && abs(vec[i-1]-vec[i]) <= 3;
        return ans;
    }

    void solve() {
        for (int i = 0; i < a.size(); i++)
            if (ok(a[i])) res++;
        cout << res << '\n'; 
    }
}

namespace part2 {
    vector<int> d;
    bool check_d(int exclude) {
        int zero = 0, pos = 0, neg = 0;
        for (int i = 0; i < d.size(); i++) if (i != exclude) {
            if (d[i] > 0) pos++;
            else if (d[i] < 0) neg++;
            else zero++;
            if (abs(d[i]) > 3) return false;
        }
        return zero == 0 && min(pos, neg) == 0;
    }

    bool ok(vector<int> &vec) {
        d.clear();
        for (int i = 1; i < vec.size(); i++) d.push_back(vec[i]-vec[i-1]);
        bool ans = check_d(0) || check_d(d.size()-1); // delete vec.front() or vec.back()
        for (int i = 1; i < d.size() && !ans; i++) {
            d[i] += d[i-1];
            ans |= check_d(i-1);
            d[i] -= d[i-1];
        }
        return ans;
    }

    void solve() {
        for (int i = 0; i < a.size(); i++)
            if (ok(a[i])) res++;
        cout << res << '\n'; 
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (getline(cin, line)) {
        a.push_back(vector<int>());
        stringstream ss(line);
        int num;
        while (ss >> num) a.back().push_back(num);
    }
    part2::solve();

    return 0;
}