# Section 240

The integer parameters should really be initialized by a macro package;
the following initialization does the minimum to keep $\TeX$ from complete failure.

```c << Initialize table entries (done by INITEX only) >>+=
for(k = INT_BASE; k < DEL_CODE_BASE; k++) {
    eqtb[k].integer = 0;
}
mag = 1000;
tolerance = 10000;
hang_after = 1; max_dead_cycles = 25;
escape_char = '\\';
end_line_char = CARRIAGE_RETURN;
for(k = 0; k <= 255; k++) {
    del_code(k) = -1;
}
del_code('.') = 0; // this null delimiter is used in error recovery
```
