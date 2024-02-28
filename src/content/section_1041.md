# Section 1041

The occurrence of blank spaces is almost part of $\TeX$'s inner loop, since we usually encounter about one space for every five non-blank characters.
Therefore *main_control* gives second-highest priority to ordinary spaces.

When a glue parameter like `\spaceskip` is set to '`0pt`', we will see to it later that the corresponding glue specification is precisely *ZERO_GLUE*, not merely a pointer to some specification that happens to be full of zeroes.
Therefore it is simple to test whether a glue parameter is zero or not.

```c << Append a normal inter-word space to the current list, then |goto big_switch| >>=
if (space_skip == ZERO_GLUE) {
    // << Find the glue specification, |main_p|, for text spaces in the current font >>
    temp_ptr = new_glue(main_p);
}
else {
    temp_ptr = new_param_glue(SPACE_SKIP_CODE);
}
link(tail) = temp_ptr;
tail = temp_ptr;
goto big_switch;
```
