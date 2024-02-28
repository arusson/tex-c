# Section 741

```c << Compute the amount of skew >>=
s = 0;
if (math_type(nucleus(q)) == MATH_CHAR) {
    fetch(nucleus(q));
    if (char_tag(cur_i) == LIG_TAG) {
        a = lig_kern_start(cur_f, cur_i);
        cur_i = font_info[a];
        if (skip_byte(cur_i) > STOP_FLAG) {
            a = lig_kern_restart(cur_f, cur_i);
            cur_i = font_info[a];
        }
        while(true) {
            if (next_char(cur_i) == skew_char[cur_f]) {
                if (op_byte(cur_i) >= KERN_FLAG && skip_byte(cur_i) <= STOP_FLAG) {
                    s = char_kern(cur_f, cur_i);
                }
                break; // goto done1
            }
            if (skip_byte(cur_i) >= STOP_FLAG) {
                break; // goto done1
            }
            a += skip_byte(cur_i) + 1;
            cur_i = font_info[a];
        }
    }
}
// done1:
```
