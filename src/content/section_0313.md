# Section 313

This routine should be changed, if necessary, to give the best possible indication of where the current line resides in the input file.
For example, on some systems it is best to print both a page and line number.

```c << Print location of current line >>=
if (name <= 17) {
    if (terminal_input) {
        if (base_ptr == 0) {
            print_nl("<*>");
        }
        else {
            print_nl("<insert> ");
        }
    }
    else {
        print_nl("<read ");
        if (name == 17) {
            print_char('*');
        }
        else {
            print_int(name - 1);
        }
        print_char('>');
    }
}
else {
    print_nl("l.");
    print_int(line);
}
print_char(' ');
```
