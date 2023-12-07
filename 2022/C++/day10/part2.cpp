#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string cmd, crt[6];
int argg, cycle = 0;
int x = 1;

void addx();
void noop();
void process_crt();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 0; i < 6; i++)
        crt[i] = string(40, '.');
    string line;
    //process_crt();
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
    for (int i = 0; i < 6; i++)
        cout << crt[i] << '\n';

    return 0;
}

void addx()
{
    for (int _ = 0; _  < 2; _++)
    {
        cycle++;
        process_crt();
        x += _*argg;
    }
}
void noop()
{
    cycle++;
    process_crt();
}

void process_crt()
{
    if (x-1 <= (cycle-1)%40 && (cycle-1)%40 <= x+1)
        crt[(cycle-1)/40][(cycle-1)%40] = '#';
}
