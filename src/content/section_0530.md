# Section 530

If some trouble arises when $\TeX$ tries to open a file, the following routine calls upon the user to supply another file name.
Parameter&nbsp;*s* is used in the error message to identify the type of file;
parameter&nbsp;*e* is the default extension if none is given.
Upon exit from the routine, variables *cur_name*, *cur_area*, *cur_ext*, and *name_of_file* are ready for another attempt at file opening.

> ![NOTE]
> String `".tex"` is added in the pool.

```c << Read the other strings >>+=
put_string(".tex"); // TEX_EXT: 261
```

```c << Internal strings numbers in the pool >>+=
#define TEX_EXT 261
```

```c io/terminal.c
void prompt_file_name(char *s, str_number e) {
    int k; // index into |buffer|
    if (strcmp(s, "input file name") == 0) {
        print_err("I can't find file `");
    }
    else {
        print_err("I can't write on file `");
    }
    print_file_name(cur_name, cur_area, cur_ext);
    print("'.");
    if (e == TEX_EXT) {
        show_context();
    }
    print_nl("Please type another ");
    print(s);
    if (interaction < SCROLL_MODE) {
        fatal_error("*** (job aborted, file error in nonstop mode)");
    }
    clear_terminal;
    prompt_input(": ");
    // << Scan file name in the buffer >>
    if (cur_ext == EMPTY_STRING) {
        cur_ext = e;
    }
    pack_cur_name;
}
```
