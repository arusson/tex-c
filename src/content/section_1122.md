# Section 1122

We need only one more thing to complete the horizontal mode routines, namely the `\accent` primitive.

```c << Cases of |main_control| that build boxes and lists >>+=
case HMODE + ACCENT:
    make_accent();
    break;
```
