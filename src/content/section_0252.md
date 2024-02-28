# Section 252

Here is a procedure that displays the contents of *eqtb[n]* symbolically.

```c io/other_printing.c
#ifdef STAT
void show_eqtb(pointer n) {
    if (n < ACTIVE_BASE) {
        print_char('?'); // this can't happen
    }
    else if (n <GLUE_BASE) {
        // << Show equivalent |n|, in region 1 or 2 >>
    }
    else if (n <LOCAL_BASE) {
        // << Show equivalent |n|, in region 3 >>
    }
    else if (n <INT_BASE) {
        // << Show equivalent |n|, in region 4 >>
    }
    else if (n <DIMEN_BASE) {
        // << Show equivalent |n|, in region 5 >>
    }
    else if (n <=EQTB_SIZE) {
        // << Show equivalent |n|, in region 6 >>
    }
    else {
        print_char('?'); // this can't happen either
    }
}
#endif
```
