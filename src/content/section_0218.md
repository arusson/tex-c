# Section 218

Here is a procedure that displays what $\TeX$ is working on, at all levels.

```c io/other_printing.c
void show_activities() {
    int p;         // index into |nest|
    int m;         // mode
    memory_word a; // auxiliary
    pointer q, r;  // for showing the current page
    int t;         // ditto

    nest[nest_ptr] = cur_list; // put the top level into the array
    print_nl("");
    print_ln();
    for(p = nest_ptr; p >= 0; p--) {
        m = nest[p].mode_field;
        a = nest[p].aux_field;
        print_nl("### ");
        print_mode(m);
        print(" entered at line ");
        print_int(abs(nest[p].ml_field));
        if (m == HMODE && nest[p].pg_field != 0x830000) {
            print(" (language");
            print_int(nest[p].pg_field % 0x10000);
            print(":hyphenmin");
            print_int(nest[p].pg_field / 0x400000);
            print_char(',');
            print_int((nest[p].pg_field / 0x10000) % 64);
            print_char(')');
        }
        if (nest[p].ml_field < 0) {
            print(" (\\output routine)");
        }
        if (p == 0) {
            // << Show the status of the current page >>
            if (link(CONTRIB_HEAD) != null) {
                print_nl("### recent contributions:");
            }
        }
        show_box(link(nest[p].head_field));
        // << Show the auxiliary field, |a| >>
    }
}
```
