#include <bits/stdc++.h>
#include <regex>
using namespace std;
using ll = long long;

string s;
ll res = 0;
vector<string> op;

namespace part1 {
    regex reg("mul\\(\\d+\\,\\d+\\)");
    void parse_op(regex r) {
        smatch m;
        while (regex_search(s, m, r)) {
            op.push_back(m.str());
            s = m.suffix().str();
        }
    }

    int calc_mul (string mul) {
        regex regnum("\\d+");
        int num1, num2; smatch m;
        regex_search(mul, m, regnum); num1 = stoi(m.str());
        mul = m.suffix().str();
        regex_search(mul, m, regnum); num2 = stoi(m.str());
        return num1*num2;
    }

    void solve() {
        parse_op(reg);
        for (int i = 0, num1, num2; i < op.size(); i++) 
            res += calc_mul(op[i]);
        cout << res << '\n';
    }
}

namespace part2 {
    regex reg("(mul\\(\\d+\\,\\d+\\))|(do\\(\\))|(don\\'t\\(\\))");
    void solve() {
        part1::parse_op(reg);
        bool ok = true;
        for (int i = 0, num1, num2; i < op.size(); i++) 
            if (op[i] == "do()") ok = true;
            else if (op[i] == "don't()") ok = false;
            else if (ok) res += part1::calc_mul(op[i]);
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string line;
    freopen("input.txt", "r", stdin);
    while (getline(cin, line)) s += line;
    part2::solve();

    return 0;
}