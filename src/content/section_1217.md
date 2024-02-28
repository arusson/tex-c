# Section 1217

Here's an example of the way many of the following routines operate.
(Unfortunately, they aren't all as simple as this.)

```c << Assignments >>=
case SET_FONT:
    define(CUR_FONT_LOC, DATA, cur_chr);
    break;
```
