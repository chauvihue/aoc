#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string cmd;
int argg, cycle = 0;
ll x = 1, res = 0;

void addx();
void noop();
void check_signal();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    while (true)
    {
        getline(cin, line);
        if (line == "-1")
            break;
        stringstream ss(line);
        ss >> cmd >> argg;
        //cerr << cmd << '|' << argg << '\n';
        if (cmd == "addx")
            addx();
        else if (cmd == "noop")
            noop();
        else
            assert(false);
    }
    cout << res << '\n';

    return 0;
}

void check_signal()
{
    if ((cycle-20)%40 == 0 && cycle <= 220)
    {
        res += x*cycle;
        cerr << x << ' ' << cycle << ' ' << x*cycle << ' ' << res << "*\n";
    }
}

void addx()
{
    for (int _ = 0; _  < 2; _++)
    {
        cycle++;
        check_signal();
        x += _*argg;
    }
}
void noop()
{
    cycle++;
    check_signal();
}
