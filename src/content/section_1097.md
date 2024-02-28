# Section 1097

Insertion and adjustment and mark nodes are constructed by the following pieces of the program.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(INSERT):
case HMODE + VADJUST:
case MMODE + VADJUST:
    begin_insert_or_adjust();
    break;

any_mode(MARK):
    make_mark();
    break;
```
