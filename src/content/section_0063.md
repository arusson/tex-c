# Section 63

The procedure *print_esc* prints a string that is preceded by the user's escape character (which is usually a backslash).

> ![NOTE]
> Again, two versions are provided.

```c io/basic_printing.c
void print_esc(char *s) {
    int c;
    // << Set variable |c| to the current escape character >>
    if (c >= 0 && c < 256) {
        print_strnumber(c);
    }
    print(s);
}

// prints escape character, then |s|
void print_esc_strnumber(str_number s) {
    int c; // the escape character code
    // << Set variable |c| to the current escape character >>
    if (c >= 0 && c < 256) {
        print_strnumber(c);
    }
    slow_print(s);
}
```
