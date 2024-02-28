# Section 1334

The present section goes directly to the log file instead of using *print* commands, because there's no need for these strings to take up *str_pool* memory when a non-**stat** version of $\TeX$ is being used.

```c << Output statistics about this job >>=
if (log_opened) {
    wlog_ln(" ");
    wlog_ln("Here is how much of TeX's memory you used:");
    wlog(" %d string", str_ptr - init_str_ptr);
    if (str_ptr != init_str_ptr + 1) {
        wlog_char('s');
    }
    wlog_ln(" out of %d", MAX_STRINGS - init_str_ptr);
    wlog_ln(" %d string characters out of %d", pool_ptr - init_pool_ptr, POOL_SIZE - init_pool_ptr);
    wlog_ln(
        " %d words of memory out of %d",
        lo_mem_max - MEM_MIN + mem_end - hi_mem_min + 2,
        mem_end + 1 - MEM_MIN
    );
    wlog_ln(
        " %d multiletter control sequences out of %d",
        cs_count, HASH_SIZE
    );
    wlog(
        " %d words of font info for %d font",
        fmem_ptr, font_ptr - FONT_BASE
    );
    if (font_ptr != FONT_BASE + 1) {
        wlog_char('s');
    }
    wlog_ln(", out of %d for %d", FONT_MEM_SIZE, FONT_MAX - FONT_BASE);
    wlog(" %d hyphenation exception", hyph_count);
    if (hyph_count != 1) {
        wlog_char('s');
    }
    wlog_ln(" out of %d", HYPH_SIZE);
    wlog_ln(
        " %di,%dn,%dp,%db,%ds stack positions out of %di,%dn,%dp,%db,%ds", 
        max_in_stack,
        max_nest_stack,
        max_param_stack,
        max_buf_stack,
        max_save_stack + 6,
        STACK_SIZE,
        NEST_SIZE,
        PARAM_SIZE,
        BUF_SIZE,
        SAVE_SIZE
    );
}
```
