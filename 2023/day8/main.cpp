#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node 
{
    string id;
    Node *l, *r;
};

Node create_node(string id, Node* l = nullptr, Node* r = nullptr)
{
    Node node;
    node.id = id; node.l = l; node.r = r;

    return node;
}

const int MAX_LOOPS = 1e3;

string steps;
map<string, Node> nodes;
ll res = 1;

void move_node(Node* &cur, char chr)
{
    if (chr == 'L') cur = cur->l;
    else cur = cur->r;
}

namespace part1
{
    void solve()
    {
        Node* cur = &nodes["AAA"];
        int i = 0;
        while (cur != nullptr && cur->id != "ZZZ")
        {
            move_node(cur, steps[i]);
            res++; i = (i+1)%steps.size();
        }
        cout << res << '\n';
    }
}

namespace part2
{
    ll lcm(ll x, ll y)
    {
        return x*y/__gcd(x, y);
    }

    void solve()
    {
        vector<Node*> ghosts;
        int i = 0, k = 0, last = 0;
        for (auto p : nodes) 
        {
            string id = p.first;
            if (id[id.size()-1] == 'A') ghosts.push_back(&nodes[id]);
        }
        vector<int> loop_size;
        /*
            https://www.reddit.com/r/adventofcode/comments/18dfpub/2023_day_8_part_2_why_is_spoiler_correct/
            u/Lornedon
            You're right, it's just dumb luck / funny design. 
            The distance from the start to an end node is always 
            the [s]ame as the distance from the end node to itself.
        */
        for (int loop = 1; loop_size.size() < 6; loop++) 
        {
            for (int j = 0; j < ghosts.size(); j++) 
            {
                move_node(ghosts[j], steps[i]);
                string id = ghosts[j]->id;
                if (id.back() == 'Z') loop_size.push_back(loop);
            }
            i = (i+1)%steps.size();
        }
        for (int i = 0; i < loop_size.size(); i++) res = res*loop_size[i]/__gcd(res, 1ll*loop_size[i]);

        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    getline(cin, steps); string line, n1, n2, n3;
    getline(cin, line);
    while (getline(cin, line))
    {
        stringstream ss(line);
        ss >> n1 >> line >> n2 >> n3;
        n2 = n2.substr(1, 3); n3 = n3.substr(0, 3);
        if (nodes.find(n2) == nodes.end()) nodes[n2] = create_node(n2);
        if (nodes.find(n3) == nodes.end()) nodes[n3] = create_node(n3);
        if (nodes.find(n1) == nodes.end()) nodes[n1] = create_node(n1);
        nodes[n1].l = &nodes[n2]; nodes[n1].r = &nodes[n3];
    }
    part2::solve();
    
    return 0;
}