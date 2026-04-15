#include <iostream>
#include <string>
using namespace std;

string stack = "$";
string input;
int i = 0;

void printState(string action)
{
    cout << stack << "\t" << input.substr(i) << "\t" << action << endl;
}

void reduce()
{
    bool changed = true;

    while (changed)
    {
        changed = false;

        // ab -> S
        if (stack.size() >= 3)
        {
            int len = stack.size();
            if (stack[len - 2] == 'a' && stack[len - 1] == 'b')
            {
                stack.pop_back();
                stack.pop_back();
                stack += "S";
                printState("Reduce S->aSb");
                changed = true;
            }
        }

        // aSb -> S
        if (stack.size() >= 4)
        {
            int len = stack.size();
            if (stack[len - 3] == 'a' && stack[len - 2] == 'S' && stack[len - 1] == 'b')
            {
                stack.pop_back();
                stack.pop_back();
                stack.pop_back();
                stack += "S";
                printState("Reduce S->aSb");
                changed = true;
            }
        }
    }
}

int main()
{
    int n;
    string prod;

    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions:\n";
    for (int j = 0; j < n; j++)
        cin >> prod;

    cout << "Enter input string: ";
    cin >> input;

    input += "$";

    cout << "\nStack\tInput\tAction\n";
    cout << "-------------------------------------------\n";

    cout << stack << "\t" << input << endl;

    while (i < input.length())
    {
        char sym = input[i];

        if (sym != '$')
        {
            stack += sym;
            i++;
            printState("Shift " + string(1, sym));
            reduce();
        }
        else
        {
            i++;
            reduce();
        }
    }

    if (stack == "$S")
        printState("Accept");
    else
        printState("Reject");

    return 0;
}
