#include <bits/stdc++.h>
using namespace std;

const int maxlen = 23;
const int maxasz = 13;
const int maxcnt = 20;

vector<string> lines;
vector<vector<int>> lens;
int n, m;
long long res = 0;

namespace part2
{
    int dp[maxlen][maxasz][maxcnt][2];
    void ok_gear(int i, vector<int> a) // fill in pos-th gear as ok
    {
        for (int k = 0; k < a.size(); k++)
            for (int cnt = 1; cnt <= a[k]; k++)
            {
                if (k>0) dp[i][k][0][0] += dp[i-1][k-1][cnt][1];
                dp[i][k][cnt][0] += dp[i-1][k][cnt][0];
                dp[i][k][cnt][1] = 0;
            }
    }
    void damaged_gear(int i, vector<int> a) // fill in pos-th gear as damaged
    {
        for (int k = 0; k < a.size(); k++)
            for (int cnt = 1; cnt <= a[k]; k++)
            {
                // if (k > 0) dp[i][k][1][1] += dp[i][k-1][a[k-1]][0]+dp[i][k-1][a[k-1]][1]; 
                dp[i][k][cnt][1] += dp[i][k][cnt-1][1];
                dp[i][k][cnt][0] = 0;
            }
    }
    
    void process(string line, vector<int> a)
    {
        /*
            dp[i][k][cnt][isbroke] : in substr 0 -> i, ways to fill the '?' so that
                            the cnt-th continous subsegment of '#' has a length of k,
                            every other previous subsegement satisfies the requirement,
                            with the i-th gears (isbroke == true? broken : ok)
            base case: dp[0][0][line[0]=='#'][line[0]=='#'] = 1;
            transitions:
                for i = 1 to n-1
                if line[i] == '.': do nothing OR break a continous subsegment (if last one was '#')
                    dp[i][k][cnt][0] = dp[i-1][k][cnt][0]
                    dp[i][k][0][0] = dp[i-1][k-1][cnt][1]
                    dp[i][k][cnt][1] = 0

                if line[i] == '#': start a new subsegment (if old one is full and last gear was '.') 
                                OR append to the current subsegment (if last one was '#')
                    dp[i][k][cnt][1] += dp[i][k][cnt-1][1]
                    dp[i][k][cnt][0] = 0
                if line[i] == '?': fill in either '.' or '#'

        */
        //line = ' '+line;
        if (line[0] == '?') dp[0][0][0][0] = dp[0][0][1][1] = 1;
        dp[0][0][line[0]=='#'][line[0]=='#'] = 1;
        for (int i = 1; i < line.size(); i++)
        {
            if (line[i] == '.' || line[i] == '?') ok_gear(i, a);
            if (line[i] == '#' || line[i] == '?') damaged_gear(i, a);
            for (int j = 0; j < a.size(); j++) 
            {
                cout << a[j] << "\t\t";
                for (int k = 0; k <= a[j]; k++) cout << dp[i][j][k][0] << '|' << dp[i][j][k][1] << '\t';
                cout << endl;    
            }
            cout << '\n';
        }
    }
    void solve()
    {
        for (int i = 0; i < n; i++) process(lines[i], lens[i]);

        cout << res << '\n';
    }
}

namespace part1
{
    bool check(string line, vector<int> a)
    {
        line += '.';
        int i, j, cnt;
        for (i = 0, j = 0, cnt = 0; i < line.size(); i++)
            if (line[i] == '#') cnt++;
            else 
            {
                if (!cnt) continue;
                if (j == a.size() || cnt != a[j]) return false;
                if (cnt == a[j]) j++;
                cnt = 0;
            }
        return j == a.size();
    }
    void process(string line, vector<int> a, int pos = 0)
    { 
        if (pos >= line.size()) // at end of the string
        {
            if (check(line, a))
                res++;
            return;
        }
        if (line[pos] != '?') {process(line, a, pos+1); return;}
        line[pos] = '.';
        process(line, a, pos+1);
        line[pos] = '#';
        process(line, a, pos+1);
    }

    void solve()
    {
        for (int i = 0; i < n; i++) process(lines[i], lens[i]);

        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    while (getline(cin, line))
    {
        stringstream ss(line);  ss >> line;
        lines.push_back(line); int num; char chr;
        lens.push_back(vector<int>());
        while (ss >> num) 
        {
            lens.back().push_back(num);
            if (!(ss >> chr)) break;
        }
    }
    n = lines.size(); m = lens.size();
    part1::solve();

    return 0;
}