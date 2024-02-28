# Section 529

Here is a routine that manufactures the output file names, assuming that *job_name* $\ne$ 0.
It ignores and changes the current settings of *cur_area* and *cur_ext*.

```c include/parser.h
#define pack_cur_name pack_file_name(cur_name, cur_area, cur_ext)
```

```c parser/filenames.c
void pack_job_name(str_number s) {
    // |s = ".log"|, |".dvi"|, or |FORMAT_EXTENSION|
    cur_area = EMPTY_STRING;
    cur_ext = s;
    cur_name = job_name;
    pack_cur_name;
}
```
