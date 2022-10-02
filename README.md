# Truth Table Generator

## Purpose
This program generates a truth table for a given logical expression.
Example:
expression: `a & ( b | -c )`
will generate following table:
```
a b c | a & ( b | -c )
----------------------
1 1 1 | 1
1 1 0 | 1
1 0 1 | 0
1 0 0 | 1
0 1 1 | 0
0 1 0 | 0
0 0 1 | 0
0 0 0 | 0
```

## Instructions
1. Navigate to the root directory
2. Type `make` to compile the program
3. Run the executable using `./ttg`
- Use `-help` tag to see help page
- Use `-r` or `--reverse` to reverse the order of boolean values

## Used Algorithm
The algorithm used in this program was not intended to be efficient. It substitutes all atoms for 0 or 1 depending on the current values of the atoms. It then iterates through the entire formula to find an operator that has both neighbours, meaning that there are no negations or parentheses between the operator and its neighbours. If one exists, it replaces it with a boolean value and iterates again until only one value remains.

