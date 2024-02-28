# Section 639

```c << Flush the box from memory, showing statistics if requested >>=
#ifdef STAT
if (tracing_stats > 1) {
    print_nl("Memory usage before: ");
    print_int(var_used);
    print_char('&');
    print_int(dyn_used);
    print_char(';');
}
#endif
flush_node_list(p);
#ifdef STAT
if (tracing_stats > 1) {
    print(" after: ");
    print_int(var_used);
    print_char('&');
    print_int(dyn_used);
    print("; still untouched: ");
    print_int(hi_mem_min - lo_mem_max - 1);
    print_ln();
}
#endif
```
