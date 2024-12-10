#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Op {
    ll tval;
    vector<int> vec;
    Op(string line) {
        stringstream ss(line); int num; char chr;
        ss >> tval >> chr;
        while (ss >> num) vec.push_back(num);
    }
};

ll res = 0;
vector<Op> a;

namespace part1 {
    bool recurse(int i, ll curval, int pos = 0) {
        if (pos == a[i].vec.size()-1) return curval == a[i].tval;
        return recurse(i, curval+a[i].vec[pos+1], pos+1) || recurse(i, curval*a[i].vec[pos+1], pos+1);
    }

    void solve() {
        for (int i = 0; i < a.size(); i++) 
            if (recurse(i, a[i].vec[0])) res += a[i].tval;    
        cout << res << '\n';
    }  
} 

namespace part2 {
    bool recurse(int i, ll curval, int pos = 0) {
        if (pos == a[i].vec.size()-1) return curval == a[i].tval;
        bool add = recurse(i, curval+a[i].vec[pos+1], pos+1) ;
        bool mult = recurse(i, curval*a[i].vec[pos+1], pos+1);
        string s = to_string(curval) + to_string(a[i].vec[pos+1]), tval = to_string(a[i].tval);
        while (s.size() < tval.size()) s = '0'+s;
        bool concat = s <= tval && recurse(i, stoull(s), pos+1);
        return add || mult || concat;
    }

    void solve() {
        for (int i = 0; i < a.size(); i++) 
            if (recurse(i, a[i].vec[0])) res += a[i].tval;    
        cout << res << '\n';
    }  
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (getline(cin, line)) a.emplace_back(line);
    part2::solve();

    return 0;
}