#include <bits/stdc++.h>
#define time first
#define record second
using namespace std;
using ll = long long;

string l1, l2;
vector<pair<ll, ll>> race;
long long res = 1;

namespace part1
{
    int process_race(ll t, ll r)
    {
        int cnt = 0;
        for (ll i = 1; i < t; i++) 
            if (i*(t-i) > r) cnt++;
        return cnt;
    }

    void solve()
    {
        /*
            suppose we spent t (ms) to hold down the button
            our speed: t (mm/ms)
            out time: race[i].time - t (ms)
            distance travelled: t*(race[i].time-t) (mm)
        */
        for (int i = 0; i < race.size(); i++)
            res *= process_race(race[i].time, race[i].record);
        cout << res << '\n';
    }
}

namespace part2
{
    void solve()
    {
        string num1, num2;
        for (int i = 0; i < race.size(); i++)
        {
            num1 += to_string(race[i].time);
            num2 += to_string(race[i].record);
        }
        race.clear(); race.emplace_back(stoll(num1), stoll(num2));
        part1::solve();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    getline(cin, l1); getline(cin, l2);
    stringstream s1(l1); int num;
    s1 >> l1;
    while (s1 >> num) race.emplace_back(num, 0);
    stringstream s2(l2);
    s2 >> l2;
    for (int i = 0; i < race.size(); i++) s2 >> race[i].record;
    part2::solve();
    
    return 0;
}