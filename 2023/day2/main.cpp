#include <bits/stdc++.h>
using namespace std;

vector<string> lines;
int id, res = 0;

namespace part1
{
    int blue, red, green;
    bool parse(string line)
    {
        blue = red = green = 0;
        stringstream ss(line);
        string s; int num; char chr;
        ss >> s >> id >> s;
        while (ss >> num >> s)
        {
            string color = s.substr(0, s.size()-1);
            if (color == "blue") blue = max(blue, num);
            else if (color == "red") red = max(red, num);
            else green = max(green, num);
            if (red > 12 || green > 13 || blue > 14) return false;
        }
        return true;
    }

    void solve()
    {
        for (int i = 0; i < lines.size(); i++)
            if (parse(lines[i])) res += id;
        cout << res << '\n';
    }
}

namespace part2
{
    int blue, red, green;
    void parse(string line)
    {
        blue = red = green = 0;
        stringstream ss(line);
        string s; int num; char chr;
        ss >> s >> id >> s;
        while (ss >> num >> s)
        {
            string color;
            if (s[s.size()-1] == ';' || s[s.size()-1] == ',') color = s.substr(0, s.size()-1);
            else color = s;
            if (color == "blue") blue = max(blue, num);
            else if (color == "red") red = max(red, num);
            else green = max(green, num);
        }
    }

    void solve()
    {
        for (int i = 0; i < lines.size(); i++)
        {
            blue = red = green = 0;
            parse(lines[i]);
            res += blue*red*green;
        }
        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    string line;
    while (getline(cin, line))
    {
        if (line == "end") break;
        lines.push_back(line);
    }
    part2::solve();
    
    return 0;
}