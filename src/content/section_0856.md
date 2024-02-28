# Section 856

```c << Print a symbolic description of this feasible break >>=
if (printed_node != cur_p) {
    // << Print the list between |printed_node| and |cur_p|, then set |printed_node = cur_p| >>
}
print_nl("@");
if (cur_p == null) {
    print_esc("par");
}
else if (type(cur_p) != GLUE_NODE) {
    if (type(cur_p) == PENALTY_NODE) {
        print_esc("penalty");
    }
    else if (type(cur_p) == DISC_NODE) {
        print_esc("discretionary");
    }
    else if (type(cur_p) == KERN_NODE) {
        print_esc("kern");
    }
    else {
        print_esc("math");
    }
}
print(" via @@");
if (break_node(r) == null) {
    print_char('0');
}
else {
    print_int(serial(break_node(r)));
}
print(" b=");
if (b > INF_BAD) {
    print_char('*');
}
else {
    print_int(b);
}
print(" p=");
print_int(pi);
print(" d=");
if (artificial_demerits) {
    print_char('*');
}
else {
    print_int(d);
}
```
