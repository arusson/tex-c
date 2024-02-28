# Section 1043

```c << Declare action procedures for use by |main_control| >>=
// handle spaces when |space_factor != 1000|
void app_space() {
    pointer q; // glue node
    if (space_factor >= 2000 && xspace_skip != ZERO_GLUE) {
        q = new_param_glue(XSPACE_SKIP_CODE);
    }
    else {
        if (space_skip != ZERO_GLUE) {
            main_p = space_skip;
        }
        else {
            // << Find the glue specification, |main_p|, for text spaces in the current font >>
        }
        main_p = new_spec(main_p);
        // << Modify the glue specification in |main_p| according to the space factor >>
        q = new_glue(main_p);
        glue_ref_count(main_p) = null;
    }
    link(tail) = q;
    tail = q;
}
```
