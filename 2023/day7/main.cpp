#include <bits/stdc++.h>
using namespace std;

const string reff1 = "23456789TJQKA";
const string reff2 = "J23456789TQKA";

enum Type {high, one_pair, two_pair, three, house, four, five};

struct Card
{
    string s, reff; int b, freq['z'+3];
    Type type;
    bool existjoker;
    int part1()
    {
        set<char> st(s.begin(), s.end());
        return st.size();
    }
    int part2()
    {
        set<char> st(s.begin(), s.end());
        if (s.find('J') != string::npos) {existjoker = true; return max(1, (int)st.size()-1);}
        return st.size();
    }

    Type classify(bool part = false)
    {
        int uniq;
        if (!part) {uniq = part1(); reff = reff1;}
        else {uniq = part2(); reff = reff2;}
        if (uniq == 5) return high;
        else if (uniq == 4) return one_pair;
        else if (uniq == 3) // three of a kind OR two pairs
        {
            if (existjoker) return three; // if there is joker, it is always advantageous
            for (int i = 0, cnt; i < s.size(); i++)
            {
                cnt = 0;
                for (int j = 0; j < s.size(); j++) if (s[i] == s[j]) cnt++;
                if (cnt == 3) return three;
            }
            return two_pair;
        } else if (uniq == 2) // four of a kind OR full house
        {
            if (existjoker) // EDGE CASE
            {
                int freq['z'+3];
                memset(freq, 0, sizeof(freq));
                for (int i = 0; i < s.size(); i++) freq[s[i]]++;
                for (int i = 0; i < s.size() && freq['J'] == 1; i++) 
                    if (s[i] != 'J' && freq[s[i]] == 2) for (int j = 0; j < s.size(); j++)
                        if (s[j] != 'J' && i != j && freq[s[j]] == 2) 
                            return house; // one pair, 1 three -> house NOT FOUR
                return four;
            }
            for (int i = 0, cnt = 0; i < s.size(); i++)
            {
                cnt = 0;
                for (int j = 0; j < s.size(); j++) if (s[i] == s[j]) cnt++;
                if (cnt == 4) return four;
            }
            return house;
        }
        return five;
    }

    Card(string _s, int _b, string _r=reff1) : s(_s), b(_b), reff(_r), existjoker(false) {}
    bool operator < (const Card &a)
    {
        if (type == a.type)
        {
            for (int i = 0; i < s.size(); i++)
                if (s[i] != a.s[i]) return reff.find(s[i]) < reff.find(a.s[i]);
        }
        return type < a.type;
    }
};

vector<Card> cards;
long long res = 0;

namespace part1
{
    void solve()
    {
        for (int i = 0; i < cards.size(); i++) cards[i].type = cards[i].classify();
        sort(cards.begin(), cards.end());   
        for (int i = 0; i < cards.size(); i++)
            res += 1ll*cards[i].b*(i+1);
        cout << res << '\n';
    }
} 

namespace part2
{
    void solve()
    {
        //GREEDY: replace all J with the most frequent character
        for (int i = 0; i < cards.size(); i++) cards[i].type = cards[i].classify(true);
        sort(cards.begin(), cards.end());
        for (int i = 0; i < cards.size(); i++)
            res += 1ll*cards[i].b*(i+1);
        cout << res << '\n';
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    string card; int bid;
    while (cin >> card >> bid) cards.emplace_back(card, bid);
    part2::solve();
    
    return 0;
}