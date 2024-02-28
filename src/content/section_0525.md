# Section 525

Operating systems often make it possible to determine the exact name (and possible version number) of a file that has been opened.
The following routine, which simply makes a $\TeX$ string from the value of *name_of_file*, should ideally be changed to deduce the full name of file&nbsp;*f*, which is the file most recently opened, if it is possible to do this in a Pascal program.

This routine might be called after string memory has overflowed, hence we dare not use *'str_room'*.

> ![NOTE]
> Indexing into *name_of_file* starts from 0 instead of 1.
> 
> Functions *a_make_name_string*, *b_make_name_string*, and *w_make_name_string* have been removed.

```c parser/filenames.c
str_number make_name_string() {
    int k; // index into |name_of_file|
    if (pool_ptr + name_length > POOL_SIZE
        || str_ptr == MAX_STRINGS
        || cur_length > 0)
    {
        return '?';
    }
    else {
        for(k = 0; k < name_length; k++) {
            append_char(XORD[(int)name_of_file[k]]);
        }
        return make_string();
    }
}
```
