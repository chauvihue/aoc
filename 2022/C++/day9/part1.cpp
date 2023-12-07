#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

map<char, int> reff = {{'L', 0},
                        {'R', 1},
                        {'U', 2},
                        {'D', 3}};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

pii head, tail, gradient, tail_change;
set<pii> tail_pos = {{0, 0}};
int dir, steps;

void process();
bool check_side();
bool check_diag();

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
        dir = reff[line[0]];
        steps = stoi(line.substr(2, line.size()-2));
        process();
    }
    cout << tail_pos.size() << '\n';
    //for (auto ai : tail_pos)
        //cerr << '(' << ai.x << ", " << ai.y << ")\n";

    return 0;
}

void process()
{
    bool need_update;
    while (steps--)
    {
        tail_change = {0, 0};
        need_update = false;
        head.x += dx[dir];
        head.y += dy[dir];
        gradient = {head.x - tail.x, head.y - tail.y};
        need_update |= check_side();
        need_update |= check_diag();
        tail.x += tail_change.x;
        tail.y += tail_change.y;
        if (need_update)
            tail_pos.insert(tail);
    }
}

bool check_side()
{
    // left
    if (gradient == make_pair(-2, 0))
        tail_change = {-1, 0};
    // right
    else if (gradient == make_pair(2, 0))
        tail_change = {1, 0};
    // up
    else if (gradient == make_pair(0, -2))
        tail_change = {0, -1};
    // down
    else if (gradient == make_pair(0, 2))
        tail_change = {0, 1};
    else return false;
    return true;
}

bool check_diag()
{
    // upleft
    if (gradient == make_pair(-1, -2) || gradient == make_pair(-2, -1))
        tail_change = {-1, -1};
    // upright
    else if (gradient == make_pair(1, -2) || gradient == make_pair(2, -1))
        tail_change = {1, -1};
    // downleft
    else if (gradient == make_pair(-1, 2) || gradient == make_pair(-2, 1))
        tail_change = {-1, 1};
    // downright
    else if (gradient == make_pair(1, 2) || gradient == make_pair(2, 1))
        tail_change = {1, 1};
    else return false;
    return true;
}
