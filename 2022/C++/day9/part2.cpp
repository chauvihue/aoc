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

pii knot[10], gradient, tail_change;
set<pii> tail_pos = {{0, 0}};
int dir, steps;

void process();
void simulate_knots(int head = 1, int tail = 2);
bool check_update(int head = 0, int tail = 1);
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
    for (int _ = 0; _ < steps; _++)
    {
        knot[0].x += dx[dir];
        knot[0].y += dy[dir];
        if (check_update())
        {
            knot[1].x += tail_change.x;
            knot[1].y += tail_change.y;
            simulate_knots();
        }
    }
}

void simulate_knots(int head, int tail)
{
    //for (int i = 0; i < 10; i++)
        //cerr << i << "\t(" << knot[i].x << ", " << knot[i].y << ")\n";
    //cerr << '\n';
    if (check_update(head, tail))
    {
        knot[tail].x += tail_change.x;
        knot[tail].y += tail_change.y;
        if (tail == 9)
            tail_pos.insert(knot[tail]);
        else
            simulate_knots(tail, tail+1);
    }
}

bool check_update(int head, int tail)
{
    tail_change = {0, 0};
    gradient = {knot[head].x - knot[tail].x, knot[head].y - knot[tail].y};
    return check_side() || check_diag();
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
    if (abs(gradient.x) == 1 && abs(gradient.y) == 1)
        return false;
    else if (gradient.x < 0 && gradient.y < 0)
        tail_change = {-1, -1};
    // upright
    else if (gradient.x > 0 && gradient.y < 0)
        tail_change = {1, -1};
    // downleft
    else if (gradient.x < 0 && gradient.y > 0)
        tail_change = {-1, 1};
    // downright
    else if (gradient.x > 0 && gradient.y > 0)
        tail_change = {1, 1};
    return true;
}
