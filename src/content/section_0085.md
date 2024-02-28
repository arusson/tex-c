# Section 85

```c << Print the menu of available options >>=
print("Type <return> to proceed, S to scroll future error messages,");
print_nl("R to run without stopping, Q to run quietly,");
print_nl("I to insert something, ");
if (deletions_allowed) {
    print_nl("1 or .... or 9 to ignore the next 1 to 9 tokens of input,");
}
print_nl("H for help, X to quit.");
```
