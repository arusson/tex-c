# Section 284

```c << Declare the procedure called |restore_trace| >>=
#ifdef STAT
// |eqtb[p]| has just been restored or retained
void restore_trace(pointer p, char *s) {
    begin_diagnostic();
    print_char('{');
    print(s);
    print_char(' ');
    show_eqtb(p);
    print_char('}');
    end_diagnostic(false);
}
#endif
```
