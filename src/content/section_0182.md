# Section 182

Now we are ready for *show_node_list* itself.
This procedure has been written to be "extra robust" in the sense that it should not crash or get into a loop even if the data structures have been messed up by bugs in the rest of the program.
You can safely call its parent routine *show_box(p)* for arbitrary values of *p* when you are debugging $\TeX$.
However, in the presence of bad data, the procedure may fetch a *memory_word* whose variant is different from the way it was stored;
for example, it might try to read *mem[p].hh* when *mem[p]* contains a scaled integer, if *p* is a pointer that has been clobbered or chosen at random.

```c io/display_boxes.c
// prints a node list symbolically
void show_node_list(int p) {
    int n;    // the number of items already printed at this level
    double g; // a glue ratio, as a floating point number
    if (cur_length > depth_threshold) {
        if (p > null) {
            // indicate that there's been some truncation
            print(" []");
        }
        return;
    }
    n = 0;
    while (p > MEM_MIN) {
        // display the nesting history
        print_ln();
        print_current_string();
        if (p > mem_end) {
            // pointer out of range
            print("Bad link, display aborted.");
            return;
        }
        incr(n);
        if (n > breadth_max) {
            // time to stop
            print("etc.");
            return;
        }
        // << Display node |p| >>
        p = link(p);
    }
}
```
