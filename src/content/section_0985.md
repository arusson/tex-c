# Section 985

```c include/io.h
#define print_plus(X, Y)                    \
    do {                                    \
        if (page_so_far[(X)] != 0) {        \
            print(" plus ");                \
            print_scaled(page_so_far[(X)]); \
            print((Y));                     \
        }                                   \
    } while (0)
```

```c io/other_printing.c
void print_totals() {
    print_scaled(page_total);
    print_plus(2, "");
    print_plus(3, "fil");
    print_plus(4, "fill");
    print_plus(5, "filll");
    if (page_shrink != 0) {
        print(" minus ");
        print_scaled(page_shrink);
    }
}
```
