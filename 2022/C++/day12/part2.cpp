#include <bits/stdc++.h>
#define row first
#define col second
using namespace std;

const string dir = "><v^";
const string dir_placeholder = "RLDU";
const int dx[] = {0, 0, -1, 1}; 
const int dy[] = {-1, 1, 0, 0};

typedef pair<int, int> pii;

int n, m, res = 0;
vector<string> lines, graph;
pair<int, int> s, src, des = {-1, -1};

pii find_chr(char chr)
{
    for (int i = 0, pos; i < n; i++)
    {
        pos = lines[i].find(chr);
        if (pos != string::npos)
            return {i, pos};
    }
    assert(false);
    return {-1, -1};
}

bool inmap (int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < m && lines[x][y] != '~' && graph[x][y] == '.';
}

void bfs()
{
    queue<pii> q;
    q.push(src);
    // finding des
    while (!q.empty())
    {
        int x = q.front().row, y = q.front().col;
        q.pop();
        for (int i = 0; i < n; i++) 
        {
            int newx = x+dx[i], newy = y+dy[i];
            if (inmap(newx, newy) && lines[newx][newy] - lines[x][y] >= -1)
            {
                graph[newx][newy] = dir[i];
                q.emplace(newx, newy);
            }
        }
        if (lines[x][y] == 'a')
        {
            des = {x, y};
            break;
        }
        lines[x][y] = '~';
    }
    cerr << "des\t=\t(" << des.row << ", " << des.col << ")\n";
    // backtrack to src
    int x = des.row, y = des.col;
    while (x != src.row || y != src.col)
    {
        int cur_dir = dir.find(graph[x][y]);
        //graph[x][y] = dir_placeholder[cur_dir];
        x -= dx[cur_dir];
        y -= dy[cur_dir];
        res++;
    }
}

void beautify_graph()
{
    for (int i = 0, cur_dir; i < n; i++)
        for (int j = 0; j < m; j++) 
        {
            cur_dir = dir_placeholder.find(graph[i][j]);
            if (cur_dir == string::npos)
                graph[i][j] = '.';
            else
                graph[i][j] = dir[cur_dir];
        }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    while (getline(cin, line))
    {
        lines.push_back(line);
    }
    n = lines.size();
    m = lines[0].size();
    graph = vector<string>(n, string(m, '.'));
    s = find_chr('S');
    src = find_chr('E');
    lines[s.row][s.col] = 'a';
    lines[src.row][src.col] = 'z';
    //cerr << '(' << src.row << ", " << src.col << ")\t(" << des.row << ", " << des.col << ")\n";

    bfs(); 
    //beautify_graph();
    graph[src.row][src.col] = 'S';
    graph[des.row][des.col] = 'E';
    for (int i = 0; i < n; i++)
        cerr << graph[i] << '\n';

    cout << res << '\n';

    return 0;
}