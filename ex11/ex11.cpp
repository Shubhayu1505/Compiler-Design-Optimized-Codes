#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cout << "Enter number of statements: ";
    cin >> n;
    cin.ignore();
    cout << "Enter the statements:\n";
    vector<string> stmts(n);
    for (int i = 0; i < n; i++)
        getline(cin, stmts[i]);
    vector<string> op(n), a1(n), a2(n), res(n);
    for (int i = 0; i < n; i++) {
        size_t eq = stmts[i].find('=');
        res[i] = stmts[i].substr(0, eq);
        string expr = stmts[i].substr(eq + 1);
        size_t p;
        if ((p = expr.find('+')) != string::npos) op[i] = "+";
        else if ((p = expr.find('-')) != string::npos) op[i] = "-";
        else if ((p = expr.find('*')) != string::npos) op[i] = "*";
        else if ((p = expr.find('/')) != string::npos) op[i] = "/";
        a1[i] = expr.substr(0, p);
        a2[i] = expr.substr(p + 1);
        a1[i].erase(remove_if(a1[i].begin(), a1[i].end(), ::isspace), a1[i].end());
        a2[i].erase(remove_if(a2[i].begin(), a2[i].end(), ::isspace), a2[i].end());
        res[i].erase(remove_if(res[i].begin(), res[i].end(), ::isspace), res[i].end());
    }
    cout << "\nQuadruple Representation\nOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < n; i++)
        cout << op[i] << "\t" << a1[i] << "\t" << a2[i] << "\t" << res[i] << endl;
    cout << "\nTriple Representation\nIndex\tOp\tArg1\tArg2\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t" << op[i] << "\t" << a1[i] << "\t" << a2[i] << endl;
    cout << "\nIndirect Triple Representation\nPointer\tIndex\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t" << i << endl;
    return 0;
}
