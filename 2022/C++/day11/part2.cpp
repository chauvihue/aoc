#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll ROUNDS = 10000;

enum Operator
{
    PLUS,
    TIMES,
    SQUARE,
};

ll MOD = 1;

class Monkey
{
    public:
        queue<ll> starting_items;
        Operator opt;
        ll opt_val, test_val, true_monkey, false_monkey, inspected_cnt = 0;

        ll cal_worry_level()
        {
            ll cur_worry_level = starting_items.front(), res;
            starting_items.pop();
            if (opt == PLUS)
                res = cur_worry_level+opt_val;
            else if (opt == TIMES)
                res = cur_worry_level*opt_val;
            else if (opt == SQUARE)
                res = cur_worry_level*cur_worry_level;
            else
                assert(false);
            return res%MOD;
        }

        void process_item();
        void process_round()
        {
            while(!starting_items.empty())
                process_item();
        }
};

vector<Monkey> monkey_vec;
stringstream lines[7];
bool running = true;
deque<ll> ma;

void Monkey::process_item()
{
    ll new_worry_level = cal_worry_level(), des_monkey;
    des_monkey = (new_worry_level%test_val == 0)?true_monkey:false_monkey; // True
    monkey_vec[des_monkey].starting_items.push(new_worry_level);
    inspected_cnt++;
}

void parse_starting_items(Monkey &monkey) // lines[1]
{
    string _;
    #define line (lines[1])
    int t;
    line >> _ >> _;
    while (line >> t)
    {
        monkey.starting_items.push(t);
        line >> _;
    }
    #undef line
}

void parse_operation(Monkey &monkey) // lines[2]
{
    string _, opt_chr, term;
    #define line (lines[2])
    int val;
    line >> _ >> _ >> _ >> _ >> opt_chr >> term;
    //cerr << opt_chr << '|' << term << '\n';
    if (opt_chr == "+")
    {
        monkey.opt = PLUS;
        monkey.opt_val = stoi(term);
    } else if (opt_chr == "*")
    {
        if (term == "old")
        {
            monkey.opt = SQUARE;
            monkey.opt_val = -1;
        }
        else
        {
            monkey.opt = TIMES;
            monkey.opt_val = stoi(term);
        }
    }
    //cerr << monkey.opt_val << '|' << monkey.opt_val << '\n';
    #undef line
}

void parse_test(Monkey &monkey) // lines[3->5]
{
    string _;
    //auto line_test = lines[3], line_true = lines[4], line_false = lines[5];
    #define line_test (lines[3])
    #define line_true (lines[4])
    #define line_false (lines[5])
    line_test >> _ >> _ >> _ >> monkey.test_val;
    line_true >> _ >> _ >> _ >> _ >> _ >> monkey.true_monkey;
    line_false >> _ >> _ >> _ >> _ >> _ >> monkey.false_monkey;
    #undef line_test
    #undef line_true
    #undef line_false
    MOD *= monkey.test_val;
}

void parse_lines()
{
    Monkey cur_monkey;
    string _;
    parse_starting_items(cur_monkey);
    parse_operation(cur_monkey);
    parse_test(cur_monkey);
    monkey_vec.push_back(cur_monkey);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (true)
    {
        for (int i = 0; i < 7; i++)
        {
            getline(cin, s);
            if (s == "-1")
            {
                running = false;
                break;
            }
            lines[i].clear();
            lines[i] << s;
        }
        if (!running)
            break;
        parse_lines();
        /*
        for (int i = monkey_vec.size()-1; i < monkey_vec.size(); i++)
        {
            #define monkey (monkey_vec[i])
            while (!monkey.starting_items.empty())
            {
                cerr << monkey.starting_items.front() << '\t';
                monkey.starting_items.pop();
            }
            cerr << '\n';
            cerr << monkey.opt << '\t' << monkey.opt_val << '\n';
            cerr << monkey.test_val << '\n';
            cerr << monkey.true_monkey << '\t' << monkey.false_monkey << "\n\n";
        }
        */
    }

    for (int i = 1; i <= ROUNDS; i++)
    {
        for (int j = 0; j < monkey_vec.size(); j++)
            monkey_vec[j].process_round();
        if (i != 1 && i != 20 && (i%1000) != 0) continue;
        cerr << "Round: " << i << '\n';
        for (int i = 0; i < monkey_vec.size(); i++)
        {
            cerr << i << '\t';
            auto q = monkey_vec[i].starting_items;
            while (!q.empty())
            {
                cerr << q.front() << ' ';
                q.pop();
            }
            cerr << '\n';
        }
        cerr << '\n';
    }

    for (int i = 0; i < monkey_vec.size(); i++)
    {
        cerr << i << '\t' << monkey_vec[i].inspected_cnt << '\n';
    }

    for (int i = 0; i < monkey_vec.size(); i++)
    {
        int cnt = monkey_vec[i].inspected_cnt;
        ma.push_back(cnt);
        if (ma.size() > 2)
        {
            for (int i = ma.size()-1; i > 0; i--) if (ma[i-1] < ma[i])
                swap(ma[i-1], ma[i]);
            ma.pop_back();
        }
    }

    cout << 1LL*ma.front()*ma.back() << '\n';

    return 0;
}
