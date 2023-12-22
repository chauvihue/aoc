#include <bits/stdc++.h>
using namespace std;

class Grid
{
    vector<string> grid;
    int n, m;
    Grid rotate_right() // return a Grid object with the original grid rotated 90 degrees clockwise
    {
        vector<string> new_grid(m);
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++)
            new_grid[i] += grid[j][i];
    
        return Grid(new_grid);
    }
    int check_horizontal() // return numbers of rows above horizontal line of reflection
    {
        // print();
        for (int i = 0, r, c; i < n-1; i++)
        {
            r = i; c = i+1;
            while (r >= 0 && c < n && grid[r] == grid[c]) r--, c++;
            if (r < 0 || c >= n) return i+1;
        }
        return 0;
    }
    int check_veritcal() // return numbers of col to the left of vertical line of reflection
    {return rotate_right().check_horizontal();}
    int count_diff(string a, string b) // return numbers of different chars between 2 equal-length strings
    {
        int ans = 0;
        for (int i = 0; i < a.size(); i++) if (a[i] != b[i]) ans++;
        return ans;
    }
    int check_horizontal_smudge() // return numbers of rows above horizontal line of reflection
                                  // NOTE: A SMUDGE MAYBE PRESENT
    {
        // print();
        for (int i = 0, r, c, cnt; i < n-1; i++)
        {
            r = i; c = i+1; cnt = 0;
            while (r >= 0 && c < n && cnt <= 1)
            {
                cnt += count_diff(grid[r], grid[c]);
                r--, c++;
            }
            if ((r < 0 || c >= n) && cnt == 1) return i+1;
        }
        return 0;
    }
    int check_veritcal_smudge() // return numbers of col to the left of vertical line of reflection
                                  // NOTE: A SMUDGE MAYBE PRESENT
    {return rotate_right().check_horizontal_smudge();}
    public:
    Grid(vector<string> g)
    {
        grid = g;
        n = g.size(); m = g[0].size();
    }
    void print()
    {
        for (int i = 0; i < n; i++) cerr << grid[i] << '\n';
        cerr << '\n'; 
    }
    int check() // check without SMUDGE
    {return 100*check_horizontal() + check_veritcal();}
    int check_smudge() // check with SMUDGE
    {return 100*check_horizontal_smudge() + check_veritcal_smudge();}
};

vector<Grid> grids;
int res = 0;

namespace part1
{
    void solve()
    {
        for (int i = 0; i < grids.size(); i++) res += grids[i].check();

        cout << res << '\n';
    }
} 

namespace part2
{
    void solve()
    {
        for (int i = 0; i < grids.size(); i++) res += grids[i].check_smudge();

        cout << res << '\n';
    }
} 


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    vector<string> cur; string line;
    while (getline(cin, line))
    {
        if (line == "") {grids.emplace_back(cur); cur.clear();}
        else cur.push_back(line); 
    }
    grids.emplace_back(cur);
    part2::solve();
    
    return 0;
}