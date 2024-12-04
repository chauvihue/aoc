#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+3;

int n = 0, a[maxn], b[maxn];
ll res = 0;

namespace part1 {
    void solve() {
        sort(a, a+n); sort(b, b+n);
        for (int i = 0; i < n; i++) res += abs(a[i]-b[i]);
        cout << res << '\n';
    }
}

namespace part2 {
    int freq[maxn];
    void solve() {
        memset(freq, 0, sizeof(freq));
        for (int i = 0; i < n; i++) freq[b[i]]++;
        for (int i = 0; i < n; i++) res += 1ll*a[i]*freq[a[i]]; 
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    while (cin >> a[n] >> b[n++]) {}
    part2::solve();

    return 0;
}