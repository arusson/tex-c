# Section 1252

```c << Assignments >>+=
case HYPH_DATA:
    if (cur_chr == 1) {
#ifdef INIT
        new_patterns();
        goto done;
#endif
        print_err("Patterns can be loaded only by INITEX");
        help0;
        error();
        do {
            get_token();
        } while (cur_cmd != RIGHT_BRACE); // flush the patterns
        return;
    }
    else {
        new_hyph_exceptions();
        goto done;
    }
```
