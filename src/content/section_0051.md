# Section 51

> ![NOTE]
> We don't read from a pool file, but some strings are still needed to be added in the string pool.
>
> This is a procedure that adds a `char *` string in the pool, with an example to add the empty string.

```c strings.c
str_number put_string(char *s) {
    int n = strlen(s);
    str_room(n);
    memcpy(&str_pool[pool_ptr], s, n);
    pool_ptr += n;
    return make_string();
}
```

```c << Read the other strings >>=
put_string(""); // Empty string, its number should be 256
```

```c include/constants.h
// << Internal strings numbers in the pool >>
```

```c << Internal strings numbers in the pool >>=
#define EMPTY_STRING 256 // ""
```