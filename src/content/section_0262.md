# Section 262

Single-character control sequences do not need to be looked up in a hash table, since we can use the character code itself as a direct address.
The procedure *print_cs* prints the name of a control sequence, given a pointer to its address in *eqtb*.
A space is printed after the name unless it is a single nonletter or an active character.
This procedure might be invoked with invalid data, so it is "extra robust".
The  individual characters must be printed one at a time using *print*, since
they may be unprintable.

```c io/basic_printing.c
// prints a purported control sequence
void print_cs(int p) {
    if (p < HASH_BASE) {
        // single character
        if (p >= SINGLE_BASE) {
            if (p == NULL_CS) {
                print_esc("csname");
                print_esc("endcsname");
                print_char(' ');
            }
            else {
                print_esc_strnumber(p - SINGLE_BASE);
                if (cat_code(p - SINGLE_BASE) == LETTER) {
                    print_char(' ');
                }
            }
        }
        else if (p < ACTIVE_BASE) {
            print_esc("IMPOSSIBLE.");
        }
        else {
            print_strnumber(p - ACTIVE_BASE);
        }
    }
    else if (p >= UNDEFINED_CONTROL_SEQUENCE) {
        print_esc("IMPOSSIBLE.");
    }
    else if (text(p) < 0 || text(p) >= str_ptr) {
        print_esc("NONEXISTENT.");
    }
    else {
        print_esc_strnumber(text(p));
        print_char(' ');
    }
}
```
