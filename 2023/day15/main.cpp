#include <bits/stdc++.h>
#define lab first
#define len second
using namespace std;

vector<string> steps;
long long res = 0;

int hash_algo(string s)
{
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        ans += s[i];
        ans *= 17;
        ans %= 256;
    }
    return ans;
}

namespace part1
{
    void solve()
    {
        for (int i = 0; i < steps.size(); i++) res += hash_algo(steps[i]);
        cout << res << '\n';
    }
}

namespace part2
{
    class Box
    {
        vector<pair<string, int>> lens;
        void op_del(string label) // set focal length of lens with label to 0
        {
            for (int i = 0; i < lens.size(); i++) if (lens[i].lab == label)
                {lens.erase(lens.begin()+i); return;}
        }
        void op_add(string label, int num) // set focal length of lens with label to num, if not append to lens
        {
            for (int i = 0; i < lens.size(); i++) if (lens[i].lab == label && lens[i].len)
                {lens[i].len = num; return;}
            lens.emplace_back(label, num);
        }
        public:
        void query(string label, char chr, int num=-1)
        {
            if (chr == '-') op_del(label);
            else if (chr == '=') op_add(label, num);
            else assert(false);
        }
        long long calc_power()
        {
            long long sum = 0;
            for (int i = 0, cnt = 0; i < lens.size(); i++) if (lens[i].len)
            {
                cnt++;
                sum += 1ll*cnt*lens[i].len;
            }
            return sum;
        }
        void print(int id)
        {
            if (lens.empty()) return;
            cerr << id << '\t';
            for (int i = 0; i < lens.size(); i++) cerr << lens[i].lab << '|' << lens[i].len << '\t'; cerr << '\n';
        }
    } boxes[256];
    void process_step(string step)
    {
        int val; 
        string label, lenstr;
        if (step[step.size()-1] == '-') // operator '-'
        {
            label = step.substr(0, step.size()-1);
            val = hash_algo(label);
            boxes[val].query(label, '-');
        } else
        {
            int pos = step.find('='); assert(pos != string::npos);
            label = step.substr(0, pos); lenstr = step.substr(pos+1, step.size()-(pos+1));
            val = hash_algo(label);
            boxes[val].query(label, '=', stoi(lenstr));
        }
    }
    void solve()
    {
        /*
            Each Box should have:
            - int id
            - vector<pair<string, int>> lens
            OBSERVATION: with each unique label, there's always no greater than one lens
            and support the following operations:
            - op "-" --> loop through lens list, if there exist a lens with label then replace
            focal length with 0
            - op "=" --> loop through lens list, if there exist a lens then replace the old 
            focal lengths with the new one
            - op calc_power --> loop through lens list, only count lens with
            focal length != 0
        */
        for (int i = 0; i < steps.size(); i++) process_step(steps[i]);
        for (int i = 0; i < 256; i++) res += boxes[i].calc_power()*(i+1);
        
        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin); string line;
    cin >> line; line += ',';
    int pos = 0, newpos = line.find(",");
    while (newpos != string::npos)
    {
        steps.push_back(line.substr(pos, newpos-pos));
        pos = newpos+1;
        newpos = line.find(",", newpos+1);
    }
    part2::solve();

    return 0;
}