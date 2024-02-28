# Section 570

We want to make sure that there is no cycle of characters linked together by *LIST_TAG* entries, since such a cycle would get $\TeX$ into an endless loop.
If such a cycle exists, the routine here detects it when processing the largest character code in the cycle.

```c include/font_metric.h
#define check_byte_range(X)         \
    do {                            \
        if ((X) < bc || (X) > ec) { \
            abort;                  \
        }                           \
    } while (0)

#define current_character_being_worked_on (k + bc - fmem_ptr)
```

```c << Check for charlist cycle >>=
check_byte_range(d);
while (d < current_character_being_worked_on) {
    qw = char_info(f, d);
    // N.B.: not |d|, since |char_base[f]| hasn't been adjusted yet
    if (char_tag(qw) != LIST_TAG) {
        goto not_found;
    }
    d = rem_byte(qw); // next character on the list
}
if (d == current_character_being_worked_on) {
    abort; // yes, there's a cycle
}
not_found:
```
