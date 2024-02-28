# Section 867

The code that passes over the characters of words in a paragraph is part of $\TeX$'s inner loop, so it has been streamlined for speed.
We use the fact that '`\parfillskip`' glue appears at the end of each paragraph;
it is therefore unnecessary to check if *link(cur_p) = null* when *cur_p* is a character node.

```c << Advance |cur_p| to the node following the present string of characters >>=
prev_p = cur_p;
do {
    f = font(cur_p);
    act_width += char_width(f, char_info(f, character(cur_p)));
    cur_p = link(cur_p);
} while (is_char_node(cur_p));
```
