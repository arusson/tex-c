# Section 485

The first line of a file must be treated specially, since *input_ln* must be told not to start with *get*.

> ![NOTE]
> No need for the boolean, see section [31](./part03.md#section-31).

```c << Input the first line of |read_file[m]| >>=
if (input_ln(read_file[m])) {
    read_open[m] = NORMAL;
}
else {
    a_close(read_file[m]);
    read_open[m] = CLOSED;
}
```
