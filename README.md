# Compiler Design Lab Exercises

A collection of C and FLEX programs implementing fundamental compiler design concepts including lexical analysis, grammar transformations, and parsing table construction.

---

## Exercise 3: Lexical Analyzer using FLEX

**Code:** [ex3.l](https://github.com/Shubhayu1505/Compiler-Design-Optimized-Codes/blob/main/ex3/ex3.l)

A lexical analyzer that identifies basic tokens from input source code.

**Token Types:**
- Keywords: `int`, `main`, `return`, `if`
- Floats (e.g., `3.14`), Integers (e.g., `42`)
- Identifiers (a-z followed by alphanumeric)
- Operators: `+ - * /`
- Symbols: `; ,`

**How to Run:**
```bash
flex ex3.l
gcc lex.yy.c -o ex3
./ex3                # Reads from input.txt
```

---

## Exercise 4: Basic FLEX Programs - Token Analysis with Statistics

**Code:** [ex4.l](https://github.com/Shubhayu1505/Compiler-Design-Optimized-Codes/blob/main/ex4/ex4.l)

Enhanced lexical analyzer with token classification and comprehensive statistics.

**Token Output Format:**
- `KEYWORD   : token` - int, main, return, if
- `IDENTIFIER: token` - variable names
- `NUMBER    : token` - integers
- `FLOAT     : token` - decimal numbers
- `OPERATOR  : token` - + - * / = < > ! & |
- `SYMBOL    : token` - ; , . ( ) { }

**Statistics Collected:**
- Lines, Words, Characters, Spaces, Tabs
- Positive/Negative numbers
- Vowel-starting words
- Uppercase/Lowercase words

**How to Run:**
```bash
flex ex4.l
gcc lex.yy.c -o ex4
./ex4                # Reads from input.txt
```

---

## Exercise 5: Elimination of Left Recursion and Left Factoring

**Code:** [ex5.c](https://github.com/Shubhayu1505/Compiler-Design-Optimized-Codes/blob/main/ex5/ex5.c)

Transforms context-free grammars by eliminating left recursion and applying left factoring.

**Features:**
- Eliminates immediate left recursion
- Performs left factoring to remove common prefixes
- Reads grammar rules from a file
- Displays original and transformed grammar

**Input Format:** `A -> α | β | γ` (one per line)

**Example (`grammar.txt`):**
```
E -> E+T | T
T -> T*F | F
F -> (E) | id
```

**How to Run:**
```bash
gcc ex5.c -o ex5
./ex5
# Choose: 1 for Left Recursion, 2 for Left Factoring
# Enter filename
```

**Output Example (Left Recursion Elimination):**
```
Original:
E -> E+T | T
T -> T*F | F
F -> (E) | id

Transformed:
E->TE'
E'->+TE'|ε
T->FT'
T'->*FT'|ε
F->(E) | id
```

---

## Exercise 7: Compute FIRST & FOLLOW for Top-Down Parsing

**Code:** [ex7.c](https://github.com/Shubhayu1505/Compiler-Design-Optimized-Codes/blob/main/ex7/ex7.c)

Computes FIRST and FOLLOW sets for a given context-free grammar.

**Features:**
- Computes FIRST sets for all non-terminals
- Computes FOLLOW sets for all non-terminals
- Handles ε (epsilon) productions ('#')
- Reads grammar from a file

**Input Format:**
- First line: Number of productions
- Following lines: `A=α` (no spaces)
- Terminals: lowercase, operators
- Non-terminals: uppercase
- Epsilon: '#'

**Example (`grammar7.txt`):**
```
3
E=TE'
E'=+TE'|#
T=FT'
T'=*FT'|#
F=(E)|id
```

**How to Run:**
```bash
gcc ex7.c -o ex7
./ex7
Enter filename: grammar7.txt
```

**Output Example:**
```
FIRST:
FIRST(E)={ ( id }
FIRST(E')={ + # }
FIRST(F)={ ( id }

FOLLOW:
FOLLOW(E)={ $ ) }
FOLLOW(E')={ $ ) }
FOLLOW(F)={ * + $ ) }
```

---

## Exercise 8: Construct a Predictive Parsing Table

**Code:** [ex8.c](https://github.com/Shubhayu1505/Compiler-Design-Optimized-Codes/blob/main/ex8/ex8.c)

Builds an LL(1) predictive parsing table for a given grammar.

**Features:**
- Computes FIRST and FOLLOW sets automatically
- Constructs LL(1) parsing table
- Handles arithmetic expression grammar
- Displays formatted table

**Grammar Handled:**
```
E  → T E'
E' → + T E' | #
T  → F T'
T' → * F T' | #
F  → id | ( E )
```

**Input Format:**
```
8
E=TE'
E'=+TE'
E'=#
T=FT'
T'=*FT'
T'=#
F=id
F=(E)
```

**How to Run:**
```bash
gcc ex8.c -o ex8
./ex8
File: grammar8.txt
```

**Output Example:**
```
PARSING TABLE
NT      id      +       *       (       )       $
E       E->T    -       -       E->T    -       -
E'      -       E'->+TE' -      -       E'->#   E'->#
T       T->F    -       -       T->F    -       -
T'      -       T'->#   T'->*FT' -      T'->#   T'->#
F       F->id   -       -       F->(E)  -       -
```

---

## Summary Table

| Ex | Program | Description | Language |
|:--:|---------|-------------|----------|
| 3 | Lexical Analyzer | Basic token identification | FLEX |
| 4 | Token Analysis | Token classification + statistics | FLEX |
| 5 | Grammar Transformation | Left recursion elimination & left factoring | C |
| 7 | FIRST & FOLLOW | Compute FIRST and FOLLOW sets | C |
| 8 | Parsing Table | Construct LL(1) predictive parsing table | C |

---
