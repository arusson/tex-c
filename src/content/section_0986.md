# Section 986

```c << Show the status of the current page >>=
if (PAGE_HEAD != page_tail) {
    print_nl("### current page:");
    if (output_active) {
        print(" (held over for next output)");
    }
    show_box(link(PAGE_HEAD));
    if (page_contents > EMPTY) {
        print_nl("total height ");
        print_totals();
        print_nl(" goal height ");
        print_scaled(page_goal);
        r = link(PAGE_INS_HEAD);
        while (r != PAGE_INS_HEAD) {
            print_ln();
            print_esc("insert");
            t = subtype(r);
            print_int(t);
            print(" adds ");
            if (count(t) == 1000) {
                t = height(r);
            }
            else {
                t = x_over_n(height(r), 1000)*count(t);
            }
            print_scaled(t);
            if (type(r) == SPLIT_UP) {
                q = PAGE_HEAD;
                t = 0;
                do {
                    q = link(q);
                    if (type(q) == INS_NODE && subtype(q) == subtype(r)) {
                        incr(t);
                    }
                } while (q != broken_ins(r));
                print(", #");
                print_int(t);
                print(" might split");
            }
            r = link(r);
        }
    }
}
```
