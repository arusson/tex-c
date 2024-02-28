# Section 645

The parameters to *hpack* and *vpack* correspond to $\TeX$'s primitives like '`\hbox to 300pt`', '`\hbox spread 10pt`';
note that '`\hbox`' with no dimension following it is equivalent to '`\hbox spread 0pt`'.
The *scan_spec* subroutine scans such constructions in the user's input, including the mandatory left brace that follows them, and it puts the specification onto *save_stack* so that the desired box can later be obtained by executing the following code:

<div align="center">
<div style="text-align: left; display: inline-block;">

*save_ptr* &larr; *save_ptr* − 2;<br>
*hpack(p, saved(1), saved(0))*.
</div>
</div>

Special care is necessary to ensure that the special *save_stack* codes are placed just below the new group code, because scanning can change *save_stack* when `\csname` appears.

```c parser/subroutines.c
// scans a box specification and left brace
void scan_spec(int c, bool three_codes) {
    int s; // temporarily saved value
    int spec_code;
    if (three_codes) {
        s = saved(0);
    }
    if (scan_keyword("to")) {
        spec_code = EXACTLY;
    }
    else if (scan_keyword("spread")) {
        spec_code = ADDITIONAL;
    }
    else {
        spec_code = ADDITIONAL;
        cur_val = 0;
        goto found;
    }
    scan_normal_dimen;
found:
    if (three_codes) {
        saved(0) = s;
        incr(save_ptr);
    }
    saved(0) = spec_code;
    saved(1) = cur_val;
    save_ptr += 2;
    new_save_level(c);
    scan_left_brace();
}
```
