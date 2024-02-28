# Section 538

Here we have to remember to tell the *input_ln* routine not to start with a *get*.
If the file is empty, it is considered to contain a single blank line.

> ![NOTE]
> The boolean argument of *input_ln* has been removed (see section [31](./part03.md#section-31)).

```c << Read the first line of the new file >>=
line = 1;
input_ln(cur_file); // ignore returned value
firm_up_the_line();
if (end_line_char_inactive) {
    decr(limit);
}
else {
    buffer[limit] = end_line_char;
}
first = limit + 1;
loc = start;
```
