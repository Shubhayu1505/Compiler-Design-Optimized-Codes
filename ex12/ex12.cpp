#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CG {
    vector<string> code;
    string t(string s) {
        size_t a = s.find_first_not_of(" \t");
        if(a == string::npos) return "";
        size_t b = s.find_last_not_of(" \t");
        return s.substr(a, b - a + 1);
    }
public:
    void gen(string s) {
        string st = t(s);
        size_t eq = st.find('=');
        if(eq == string::npos) return;
        string l = t(st.substr(0, eq));
        string r = t(st.substr(eq + 1));
        if(r.find_first_of("+-*/") == string::npos) {
            code.push_back("LOAD " + r);
            code.push_back("STORE " + l);
            return;
        }
        for(size_t i = 0; i < r.length(); i++) {
            char op = r[i];
            if(op == '+' || op == '-' || op == '*' || op == '/') {
                string o1 = t(r.substr(0, i));
                string o2 = t(r.substr(i + 1));
                string ins = (op == '+') ? "ADD" : (op == '-') ? "SUB" : (op == '*') ? "MUL" : "DIV";
                code.push_back("LOAD " + o1);
                code.push_back(ins + " " + o2);
                code.push_back("STORE " + l);
                break;
            }
        }
    }
    void disp() {
        cout << "\nTarget Code:\n";
        for(auto &c : code) cout << c << endl;
    }
};
int main() {
    CG cg;
    int n;
    cout << "Enter number of statements: ";
    cin >> n;
    cin.ignore();
    cout << "Enter statements:\n";
    for(int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        cg.gen(s);
    }
    cg.disp();
    return 0;
}
