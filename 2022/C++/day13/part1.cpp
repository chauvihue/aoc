#include <bits/stdc++.h>
#include "list.cpp"
using namespace std;

int cnt, res = 0;
vector<pair<string, string>> packs_str;

void process_packs()
{
    Packet pack1, pack2;
    for (int i = 0; i < packs_str.size(); i++)
    {
        pack1 = Packet(packs_str[i].first);
        pack2 = Packet(packs_str[i].second);
        if (pack1 < pack2 == 1)
            res += i+1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("INPUT.INP", "r", stdin);
    while (getline(cin, line))
    {
        if (cnt == 0)
            packs_str.back().first = line;
        else if (cnt == 1)
            packs_str.back().second = line;
        else
            cnt = -1;
        cnt++;
    }
    process_packs();
    cout << res << '\n';

    return 0;
}