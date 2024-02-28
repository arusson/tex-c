# Section 523

Here is the messy routine that was just mentioned.
It sets *name_of_file* from the first *n* characters of *tex_format_default*, followed by *buffer[a .. b]*, followed by the last *FORMAT_EXT_LENGTH* characters of *tex_format_default*.

We dare not give error messages here, since $\TeX$ calls this routine before the *error* routine is ready to roll.
Instead, we simply drop excess characters, since the error will be detected in another way when a strange file name isn't found.

> ![NOTE]
> Null byte is added at the end, and *tex_format_default* is indexed from 0.

```c io/dumping.c
// << Start file |dumping.c| >>

void pack_buffered_name(small_number n, int a, int b) {
    int k; // number of positions filled in |name_of_file|
    ASCII_code c; // character being packed
    int j; // index into |buffer| or |tex_format_default|
    if (n + b - a + 1 + FORMAT_EXT_LENGTH > FILE_NAME_SIZE) {
        b = a + FILE_NAME_SIZE - n - 1 - FORMAT_EXT_LENGTH;
    }
    k = 0;
    for(j = 0; j < n; j++) {
        append_to_name(XORD[(int)tex_format_default[j]]);
    }
    for(j = a; j <= b; j++) {
        append_to_name(buffer[j]);
    }
    for(j = FORMAT_DEFAULT_LENGTH - FORMAT_EXT_LENGTH; j < FORMAT_DEFAULT_LENGTH; j++) {
        append_to_name(XORD[(int)tex_format_default[j]]);
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
