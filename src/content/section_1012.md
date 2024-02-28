# Section 1012

When the page builder has looked at as much material as could appear before the next page break, it makes its decision.
The break that gave minimum badness will be used to put a completed "page" into box 255, with insertions appended to their other boxes.

We also set the values of *top_mark*, *first_mark*, and *bot_mark*.
The program uses the fact that *bot_mark* $\ne$ *null* implies *first_mark* $\ne$ *null*;
it also knows that *bot_mark = null* implies *top_mark = first_mark = null*.

The *fire_up* subroutine prepares to output the current page at the best place;
then it fires up the user's output routine, if there is one, or it simply ships out the page.
There is one parameter, *c*, which represents the node that was being contributed to the page when the decision to force an output was made.

```c << Declare the procedure called |fire_up| >>=
void fire_up(pointer c) {
    pointer p, q, r, s;          // nodes being examined and/or changed
    pointer prev_p;              // predecessor of |p|
    int n;                       // insertion box number
    bool wait;                   // should the present insertion be held over?
    int save_vbadness;           // saved value of |vbadness|
    scaled save_vfuzz;           // saved value of |vfuzz|
    pointer save_split_top_skip; // saved value of |split_top_skip|
    
    // << Set the value of |output_penalty| >>
    if (bot_mark != null) {
        if (top_mark != null) {
            delete_token_ref(top_mark);
        }
        top_mark = bot_mark;
        add_token_ref(top_mark);
        delete_token_ref(first_mark);
        first_mark = null;
    }

    // << Put the optimal current page into box 255, update |first_mark| and |bot_mark|, append insertions to their boxes, and put the remaining nodes back on the contribution list >>
    
    if (top_mark != null && first_mark == null) {
        first_mark = top_mark;
        add_token_ref(top_mark);
    }
    if (output_routine != null) {
        if (dead_cycles >= max_dead_cycles) {
            // << Explain that too many dead cycles have occurred in a row >>
        }
        else {
            // << Fire up the user's output routine and |return| >>
        }
    }
    // << Perform the default output routine >>
}
```
