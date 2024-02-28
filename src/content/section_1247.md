# Section 1247

```c << Declare subprocedures for |prefixed_command| >>+=
void alter_box_dimen() {
    small_number c; // |WIDTH_OFFSET| or |HEIGHT_OFFSET| or |DEPTH_OFFSET|
    eight_bits b; // box number
    c = cur_chr;
    scan_eight_bit_int();
    b = cur_val;
    scan_optional_equals();
    scan_normal_dimen;
    if (box(b) != null) {
        mem[box(b) + c].sc = cur_val;
    }
}
```
