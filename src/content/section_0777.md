# Section 777

```c << Scan the preamble and record it in the |preamble| list >>=
preamble = null;
cur_align = ALIGN_HEAD;
cur_loop = null;
scanner_status = ALIGNING;
warning_index = save_cs_ptr;
align_state = -1000000; // at this point, |cur_cmd = LEFT_BRACE|
while(true) {
    // << Append the current tabskip glue to the preamble list >>
    if (cur_cmd == CAR_RET) {
        break; // goto done, \cr ends the preamble
    }
    // << Scan preamble text until |cur_cmd| is |TAB_MARK| or |CAR_RET|, looking for changes in the tabskip glue; append an alignrecord to the preamble list >>
}
// done:
scanner_status = NORMAL;
```
