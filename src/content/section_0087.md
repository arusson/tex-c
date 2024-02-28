# Section 87

When the following code is executed, *buffer[(first + 1) .. (last − 1)]* may contain the material inserted by the user; otherwise another prompt will be given.
In order to understand this part of the program fully, you need to be familiar with $\TeX$'s input stacks.

```c << Introduce new material from the terminal and |return| >>=
begin_file_reading(); // enter a new syntactic level for terminal input
// now |state = MID_LINE|, so an initial blank space will count as a blank
if (last > first + 1) {
    loc = first + 1;
    buffer[first] = ' ';
}
else {
    prompt_input("insert>");
    loc = first;
}
first = last;
cur_input.limit_field = last - 1;  // no |end_line_char| ends this line
return;
```
