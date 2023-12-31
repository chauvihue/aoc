#include <bits/stdc++.h>
#define pqT priority_queue<Range, vector<Range>, comp>
using namespace std;
using ll = long long;
/*
    Basically:

    src-to-des map:
    l1   l2   len
    ...

    l2       corresponds to  l1
    l2 + 1   corresponds to  l1 + 1
    ...
    l2 + len corresponds to  l1 + len
*/
struct Range
{
    ll l, r, delta;
    Range(ll _l, ll _r, ll _d): l(_l), r(_r), delta(_d) {};
    bool operator < (const Range &p) {return l < p.l;}
};

struct comp
{
    bool operator() (const Range &a, const Range &b) {return a.delta == b.delta ? (a.l < b.l) : a.delta < b.delta;}
};

vector<ll> seeds;
vector<Range> maps[7];
ll res = LLONG_MAX;

int lowbound(ll val, vector<Range> m) // find maximum index i satisifies m[i].l <= val
{
    int l = 0, r = m.size()-1, pos = -1;
    while (l <= r)
    {
        int mid = (0ll+l+r)>>1;
        if (m[mid].l <= val)
        {
            pos = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return pos;
}

namespace part1
{
    ll convert(ll val, vector<Range> m) // convert source value val to destination value with map m
        {
            int pos = lowbound(val, m);
            if (m[pos].r < val) // pos is before the smallest range OR isnt in range m[pos] and m[pos+1]
                return val;
            return val + m[pos].delta;
        }
    void solve()
    {
        for (int i = 0; i < 7; i++) {maps[i].emplace_back(-1, -1, 0); sort(maps[i].begin(), maps[i].end());}
        for (int i = 0; i < seeds.size(); i++)
        {
            ll val = seeds[i];
            for (int j = 0; j < 7 && val >= 0; j++) val = convert(val, maps[j]);
            if (val < 0) assert(false);
            res = min(res, val);
        }
        cout << res << '\n';
    }   
}

namespace part2
{
    void process_range(pqT &pq, ll l, ll r, int k) // map range [l, r] with map maps[k] 
    {
        if (k == 7) {res = min(res, l); return;}
        int pos = lowbound(l, maps[k]);
        for (int i = pos; i < maps[k].size() && l <= r; i++)
        {
            ll d, rr;            
            if (l <= maps[k][i].r) // l is in a mapped range
            {
                d = maps[k][i].delta;
                rr = min(r, maps[k][i].r); 
            }
            else // l isnt mapped
            {
                d = 0;
                rr = min(r, maps[k][i+1].r-1); 
            }
            pq.emplace(l+d, rr+d, k+1);
            l = rr + 1;
        }
    }

    void solve()
    {
        for (int i = 0; i < 7; i++) 
        {
            maps[i].emplace_back(-1, -1, 0); maps[i].emplace_back(LLONG_MAX, LLONG_MAX, 0);
            sort(maps[i].begin(), maps[i].end());
        }
        pqT pq;
        for (int i = 0; i < seeds.size(); i += 2) pq.emplace(seeds[i], seeds[i]+seeds[i+1]-1, 0);
        ll l, r, k;
        while (!pq.empty())
        {
            if (l == pq.top().l && r == pq.top().r && k == pq.top().delta) {pq.pop(); continue;}
            ll l = pq.top().l, r = pq.top().r; int k = pq.top().delta; pq.pop();
            process_range(pq, l, r, k);
        }
        cout << res << '\n';
    }   
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    string line;
    getline(cin, line);
    stringstream ss(line); ll num;
    ss >> line;
    while (ss >> num) {seeds.push_back(num);}
    getline(cin, line); getline(cin, line);
    int cur = 0;
    ll l1, l2, len;
    while (getline(cin, line))
    {
        if (!isdigit(line[0])) {cur++; getline(cin, line); continue;}// start of new map
        stringstream ss(line);
        ss >> l1 >> l2 >> len;
        maps[cur].emplace_back(l2, l2+len-1, l1-l2);
    }
    part2::solve();
    
    return 0;
}