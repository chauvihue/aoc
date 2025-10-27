#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int maxs_sz = 1e5;

string s;
ll res = 0;

namespace part1 {
    ll pos = s[0]-'0';

    ll sum_range(ll l, int d) {return 1ll*(l+l+d-1)*d>>1;}

    void process_filei(int &i) {
        res += 1ll*(i>>1)*sum_range(pos, s[i]-'0'); 
        pos += s[i++]-'0';
    }

    void solve() {
        int i = 1; pos = s[0]-'0';
        for (int j = s.size()-1-(s.size()&1==0), numi, numj; i < j; j -= 2) while (i < j && s[j] > '0') {
            numi = s[i]-'0'; numj = s[j] - '0';
            res += 1ll*(j>>1)*sum_range(pos, min(numi, numj));
            pos += min(numi, numj);
            if (numj == numi) {s[j] = '0'; process_filei(++i);}
            else if (numj < numi) {s[j] ='0'; s[i] -= numj;}
            else {s[j] -= numi; process_filei(++i);}
        }
        cout << res << '\n';
    }
}

namespace part2 {
    ll pos;

    int calc_sz(pii p) {return p.second-p.first+1;}

    struct comp{
        bool operator () (const pii &a, const pii &b) const {
            return calc_sz(a) > calc_sz(b) || (calc_sz(a) == calc_sz(b) && a.first < b.first);
        }
    };
   
    vector<pii> space;

    struct Segtree {
        int sz = 0; vector<pii> seg; vector<int> ma;

        void init(int id, int l, int r) {
            if (sz == 0) {sz = space.size(); seg = vector<pii>((sz<<2)+2); ma = vector<int>((sz<<2)+2, 0);}
            if (l == r) {seg[id] = space[l]; ma[id] = calc_sz(space[l]); return;}
            int mid = (l+r)>>1;
            init(id<<1, l, mid); init((id<<1)+1, mid+1, r);

            if (ma[id<<1] >= ma[(id<<1)+1]) ma[id] = ma[id<<1], seg[id] = seg[id<<1];
            else ma[id] = ma[(id<<1)+1], seg[id] = seg[(id<<1)+1];
        }

        void update(int id, int l, int r, int pos, pii p={0, 0}) {
            if (pos < l || r < pos) return;
            if (l == r) {seg[id] = p; ma[id] = calc_sz(p); return;}
            int mid = (l+r)>>1;
            update(id<<1, l, mid, pos, p); update((id<<1)+1, mid+1, r, pos, p);
            
            if (ma[id<<1] >= ma[(id<<1)+1]) ma[id] = ma[id<<1], seg[id] = seg[id<<1];
            else ma[id] = ma[(id<<1)+1], seg[id] = seg[(id<<1)+1];
        }

        pii get(int id, int l, int r, int pos, int sz) { // find blocks ranging from [1..pos]
            if (pos < space[l].first) return {0,0};
            if (pos <= space[r].second && ma[id] >= sz && seg[id].second <= pos) return seg[id];
            int mid = (l+r)>>1;
            if (ma[id<<1] >= sz) return get(id<<1, l, mid, pos, sz);
            else return get((id<<1)+1, mid+1, r, pos, sz);
        }
    } segtree;


    ll calc_blocki (int i) {
        int sz = s[i]-'0';
        /*
            find the first pair with size >= sz in array space
            --> maintain a SEGMENT TREE that keep track of max size
            in the prefix [1..i]
            --> to find the first pair space[k] that satisfies,
            we WALK ON THE SEGMENT TREE
            
            when moving the file to the new space leads to:
            - inserting the remaining space --> update the size and the max accordingly
            - deleting the space all together --> update the size as 0 and recalculate the max accordingly
        */
        pii newspace = segtree.get(1, 1, space.size()-1, pos, sz);
        cout << newspace.first << ' ' << newspace.second << '\n';
    }

    void solve() {
        pos = 0;
        space.emplace_back(0, 0);
        for (int i = 0; i < s.size(); i++) if (s[i] != '0') {
            if (i&1) space.emplace_back(pos, pos+s[i]-'0'-1); 
            pos += s[i]-'0';
        }
        segtree.init(1, 1, space.size()-1);
        for (int i = s.size()-1; i >= 0; i -= 2) {
            pos -= s[i]-'0'+1;
            res += calc_blocki(i);
            if (i-1 >= 0 && s[i-1] != '0') {
                pos -= s[i-1]-'0';
                pii temp = {pos, pos+s[i-1]-'0'-1};
                
            }
        }
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> s;
    part2::solve();

    return 0;
}