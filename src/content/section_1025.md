# Section 1025

```c << Fire up the user's output routine and |return| >>=
output_active = true;
incr(dead_cycles);
push_nest();
mode = -VMODE;
prev_depth = IGNORE_DEPTH;
mode_line = -line;
begin_token_list(output_routine, OUTPUT_TEXT);
new_save_level(OUTPUT_GROUP);
normal_paragraph();
scan_left_brace();
return;
```
