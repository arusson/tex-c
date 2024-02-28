# Section 60

Control sequence names, file names, and strings constructed with `\string` might contain *ASCII_code* values that can't be printed using *print_char*.
Therefore we use *slow_print* for them:

```c io/basic_printing.c
// prints string s
void slow_print(int s) {
    pool_pointer j; // current character code position
    if (s >= str_ptr || s < 256) {
        print_strnumber(s);
    }
    else {
        j = str_start[s];
        while (j < str_start[s + 1]) {
            print_strnumber(str_pool[j]);
            incr(j);
        }
    }
}
```
