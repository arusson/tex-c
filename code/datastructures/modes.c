// ~~~ Section 216 ~~~
// ~~~ Start file |modes.c|, 1382 ~~~
#include "datastructures.h"
#include "texerror.h"
// ~~~ End section 1382 ~~~

// enter a new semantic level, save the old
void push_nest() {
    if (nest_ptr > max_nest_stack) {
        max_nest_stack = nest_ptr;
        if (nest_ptr == NEST_SIZE) {
            overflow("semantic nest size", NEST_SIZE);
        }
    }
    nest[nest_ptr] = cur_list; // stack the record
    incr(nest_ptr);
    head = get_avail();
    tail = head;
    prev_graf = 0;
    mode_line = line;
}
// ~~~ End section 216 ~~~

// ~~~ Section 217 ~~~
// leave a semantic level, re-enter the old
void pop_nest() {
    free_avail(head);
    decr(nest_ptr);
    cur_list = nest[nest_ptr];
}
// ~~~ End section 217 ~~~
