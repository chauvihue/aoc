#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*struct DIR
{
    int id;
    ll sz = 0;
};*/

const int maxN = 1e5;
const int THRESHOLD = 100000;

map<string, int> id_lookup = {{".", 1}};
map<int, string> name_lookup = {{1, "."}};
// name_lookup is SOLELY for debugging purposes
vector<vector<int>> hierarchy(1, vector<int>());
string line, _, cmd, param, cur_name = ".";
stringstream tokens;
int cur_id = 1, max_id = 1;
bool is_running = true;
ll sz[maxN], res = 0;

void cd();
void ls();
void dfs(int id = 1);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    getline(cin, line);
    tokens << line;
    while (line != "-1")
    {
        tokens >> _ >> cmd >> param;
        //cerr << cmd << '|' << param << endl;
        if (cmd == "cd")
            cd();
        else if (cmd == "ls")
            ls();
        else assert(false);
        if (!is_running)
            break;
        tokens.clear();
        tokens << line;
    }
    dfs();

    for (int i = 1; i <= hierarchy.size(); i++)
    {
        cerr << i << "\t\t";
        for (int j = 0; j < hierarchy[i].size(); j++)
            cerr << hierarchy[i][j] << '|' << sz[hierarchy[i][j]] << "\t";
        cerr << '\n';
    }
    cerr << '\n';
    for (int i = 1; i <= hierarchy.size(); i++)
        cerr << name_lookup[i] << "\t\t" << sz[i] << '\n';

    cout << res << '\n';
    return 0;
}

void cd()
{
    if (param == "..")
    {
        cur_name = cur_name.substr(0, cur_name.rfind('/'));
    } else if (param != "/")
    {
        cur_name += "/"+param;
        //hierarchy.resize(hierarchy.size()+1);
        //id_lookup[cur_name] = hierarchy.size();
    }
    cur_id = id_lookup[cur_name];
    //cerr << cur_name << '|' << cur_id << endl;
    getline(cin, line);
}

void ls()
{
    string param1, param2, newfile_name;
    getline(cin, line);
    while (line[0] != '$')
    {
        tokens.clear();
        tokens << line;
        tokens >> param1 >> param2;

        newfile_name = cur_name+"/"+param2;
        hierarchy.resize(hierarchy.size()+1);
        max_id = hierarchy.size();
        //cerr << newfile_name << '\n';
        // ----------------------
        name_lookup[max_id] = newfile_name;
        // FOR DEBUGGING
        //cerr << newfile_name << ' ' << max_id;

        id_lookup[newfile_name] = max_id;
        hierarchy[cur_id].push_back(max_id);

        //cerr << param1 << '|' << param2 << '|' << newfile_name << '|' << max_id << '\n';

        //cerr << param1 << '|' << param2 << '\n';

        if (param1 != "dir")
            sz[max_id] = stoi(param1);

        if (line == "-1")
        {
            is_running = false;
            break;
        }
        getline(cin, line);
    }
    is_running = line != "$ -1";
}

void dfs(int id)
{
    for (int i = 0; i < hierarchy[id].size(); i++)
    {
        dfs(hierarchy[id][i]);
        sz[id] += sz[hierarchy[id][i]];
    }
    if (!hierarchy[id].empty() && sz[id] <= THRESHOLD)
        res += sz[id];
}
