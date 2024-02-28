# Section 1355

Each new type of node that appears in our data structure must be capable of being displayed, copied, destroyed, and so on.
The routines that we need for write-oriented whatsits are somewhat like those for mark nodes;
other extensions might, of course, involve more subtlety here.

```c io/other_printing.c
void print_write_whatsit(char *s, pointer p) {
    print_esc(s);
    if (write_stream(p) < 16) {
        print_int(write_stream(p));
    }
    else if (write_stream(p) == 16) {
        print_char('*');
    }
    else {
        print_char('-');
    }
}
```
