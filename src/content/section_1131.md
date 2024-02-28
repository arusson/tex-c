# Section 1131

An *ALIGN_GROUP* code is supposed to remain on the *save_stack* during an entire alignment, until *fin_align* removes it.

A devious user might force an *ENDV* command to occur just about anywhere;
we must defeat such hacks.

```c builder/boxes_and_lists.c
void do_endv() {
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input;
    while (input_stack[base_ptr].index_field != V_TEMPLATE
        && input_stack[base_ptr].loc_field == null
        && input_stack[base_ptr].state_field == TOKEN_LIST)
    {
        decr(base_ptr);
    }
    if (input_stack[base_ptr].index_field != V_TEMPLATE
        || input_stack[base_ptr].loc_field != null
        || input_stack[base_ptr].state_field != TOKEN_LIST)
    {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    if (cur_group == ALIGN_GROUP) {
        end_graf();
        if (fin_col()) {
            fin_row();
        }
    }
    else {
        off_save();
    }
}
```
