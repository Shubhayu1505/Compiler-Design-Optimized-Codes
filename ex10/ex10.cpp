#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Prod {
    char l;
    string r;
    int n;
    Prod(char a, string b, int c) : l(a), r(b), n(c) {}
};

struct Item {
    char l;
    string r;
    int d;
    Item(char a, string b, int c) : l(a), r(b), d(c) {}
    bool done() const { return d >= r.length(); }
    char next() const { return d < r.length() ? r[d] : 0; }
    bool operator<(const Item& o) const {
        return l < o.l || (l == o.l && r < o.r) || (l == o.l && r == o.r && d < o.d);
    }
    bool operator==(const Item& o) const { return l == o.l && r == o.r && d == o.d; }
    string str() const {
        string s; s += l; s += " -> ";
        for (int i = 0; i <= r.length(); i++) {
            if (i == d) s += ".";
            if (i < r.length()) s += r[i];
        }
        return s;
    }
};

struct State {
    set<Item> i;
    int n;
    State(int a) : n(a) {}
    bool operator==(const State& o) const { return i == o.i; }
};

class LR0 {
    vector<Prod> p, ap;
    char ss;
    set<char> nt, t;
    vector<State> st;
    map<pair<int, char>, int> gt;

public:
    void read() {
        int n;
        cout << "Enter number of productions: ";
        cin >> n; cin.ignore();
        cout << "Enter productions:\n";
        for (int i = 0; i < n; i++) {
            string s; getline(cin, s);
            s.erase(remove(s.begin(), s.end(), ' '), s.end());
            nt.insert(s[0]);
            size_t x = s.find("->");
            if (x == string::npos) x = 1;
            string rhs = s.substr(x + 2);
            p.push_back(Prod(s[0], rhs, i + 1));
            for (char c : rhs) isupper(c) ? nt.insert(c) : t.insert(c);
        }
        ss = p[0].l;
    }

    void aug() {
        ap.push_back(Prod('Z', string(1, ss), 0));
        for (auto& x : p) ap.push_back(x);
        nt.insert('Z'); ss = 'Z';
    }

    set<Item> close(set<Item> s) {
        bool ch = 1;
        while (ch) {
            ch = 0; set<Item> n = s;
            for (auto& it : s) if (!it.done()) {
                char c = it.next();
                if (nt.count(c)) for (auto& pr : ap) if (pr.l == c) {
                    Item x(pr.l, pr.r, 0);
                    if (n.insert(x).second) ch = 1;
                }
            }
            s = n;
        }
        return s;
    }

    set<Item> go(const set<Item>& s, char c) {
        set<Item> r;
        for (auto& it : s) if (!it.done() && it.next() == c)
            r.insert(Item(it.l, it.r, it.d + 1));
        return close(r);
    }

    void build() {
        set<Item> x; x.insert(Item(ss, ap[0].r, 0));
        State s0(0); s0.i = close(x); st.push_back(s0);
        bool ch = 1; int ns = 1;
        while (ch) {
            ch = 0; int cs = st.size();
            for (int i = 0; i < cs; i++) {
                set<char> sy;
                for (auto& it : st[i].i) if (!it.done()) sy.insert(it.next());
                for (char c : sy) {
                    set<Item> ni = go(st[i].i, c);
                    if (ni.empty()) continue;
                    bool ex = 0; int en = -1;
                    for (int j = 0; j < st.size(); j++) if (st[j].i == ni) { ex = 1; en = st[j].n; break; }
                    if (!ex) { State t(ns++); t.i = ni; st.push_back(t); gt[{st[i].n, c}] = t.n; ch = 1; }
                    else gt[{st[i].n, c}] = en;
                }
            }
        }
    }

    void out() {
        cout << "\n1. Numbering the productions:\n";
        for (size_t i = 1; i < ap.size(); i++) cout << i << ". " << ap[i].l << " -> " << ap[i].r << endl;
        cout << "\n2. Augmented Grammar:\nS' -> " << ap[0].r << endl;
        for (size_t i = 1; i < ap.size(); i++) cout << ap[i].l << " -> " << ap[i].r << endl;
        cout << "\n3. LR(0) Items\n";
        sort(st.begin(), st.end(), [](State& a, State& b) { return a.n < b.n; });
        for (auto& s : st) {
            cout << "\nI" << s.n << ":\n";
            for (auto& it : s.i) cout << "    " << it.str() << endl;
        }
        cout << "\nGoto Transitions:\n";
        for (auto& x : gt) cout << "Goto (I" << x.first.first << ", " << x.first.second << ") = I" << x.second << endl;
    }

    void run() { read(); aug(); build(); out(); }
};

int main() {
    LR0 x; x.run();
    return 0;
}
