# Section 1293

```c io/other_printing.c
void show_whatever() {
    switch (cur_chr) {
    case SHOW_LISTS_CODE:
        begin_diagnostic();
        show_activities();
        break;
    
    case SHOW_BOX_CODE:
        // << Show the current contents of a box >>
        break;
    
    case SHOW_CODE:
        // << Show the current meaning of a token, then |goto common_ending| >>
    
    default:
        // << Show the current value of some parameter or register, then |goto common_ending| >>
    }
    // << Complete a potentially long \show command >>
common_ending:
    if (interaction < ERROR_STOP_MODE) {
        help0;
        decr(error_count);
    }
    else if (tracing_online > 0) {
        help3("This isn't an error message; I'm just \\showing something.")
            ("Type `I\\show...' to show more (e.g., \\show\\cs,")
            ("\\showthe\\count10, \\showbox255, \\showlists).");
    }
    else {
        help5("This isn't an error message; I'm just \\showing something.")
            ("Type `I\\show...' to show more (e.g., \\show\\cs,")
            ("\\showthe\\count10, \\showbox255, \\showlists).")
            ("And type `I\\tracingonline = 1\\show...' to show boxes and")
            ("lists on your terminal as well as in the transcript file.");
    }
    error();
}
```
