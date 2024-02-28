# Section 519

Another system-dependent routine is needed to convert three internal $\TeX$ strings into the *name_of_file* value that is used to open files.
The present code allows both lowercase and uppercase letters in the file name.

> ![NOTE]
> A macro *append_to_name_nul* is defined to add null byte at the end of the name.
> Writing spaces after the name has been removed.

```c include/parser.h
#define append_to_name(X)              \
    do {                               \
        c = (X);                       \
        if (k < FILE_NAME_SIZE) {      \
            name_of_file[k] = XCHR[c]; \
        }                              \
        incr(k);                       \
    } while (0)

#define append_to_name_nul name_of_file[name_length] = '\0'
```

```c parser/filenames.c
void pack_file_name(str_number n, str_number a, str_number e) {
    int k; // number of positions filled in |name_of_file|
    ASCII_code c; // character being packed
    int j; // index into |str_pool|
    k = 0;
    for(j = str_start[a]; j <= str_start[a + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    for(j = str_start[n]; j <= str_start[n + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    for(j = str_start[e]; j <= str_start[e + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    if (k <= FILE_NAME_SIZE) {
        name_length = k;
    }
    else {
        name_length = FILE_NAME_SIZE;
    }
    append_to_name_nul;
}
```
