# Section 532

Here's an example of how these conventions are used.
Whenever it is time to ship out a box of stuff, we shall use the macro *ensure_dvi_open*.

> ![NOTE]
> String `".dvi"` is added in the pool.

```c << Read the other strings >>+=
put_string(".dvi"); // DVI_EXT: 262
```

```c << Internal strings numbers in the pool >>+=
#define DVI_EXT 262
```

```c include/dvi.h
// << Start file |dvi.h| >>

#define ensure_dvi_open                                            \
    do {                                                           \
        if (output_file_name == 0) {                               \
            if (job_name == 0) {                                   \
                open_log_file();                                   \
            }                                                      \
            pack_job_name(DVI_EXT);                                \
            while (!b_open_out(&dvi_file)) {                        \
                prompt_file_name("file name for output", DVI_EXT); \
            }                                                      \
            output_file_name = make_name_string();                 \
        }                                                          \
    } while (0)
```

```c << Global variables >>+=
byte_file dvi_file;          // the device-independent output goes here
str_number output_file_name; // full name of the output file
str_number log_name;         // full name of the log file
```

