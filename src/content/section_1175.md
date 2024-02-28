# Section 1175

Subscripts and superscripts are attached to the previous nucleus by the action procedure called *sub_sup*.
We use the facts that *SUB_MARK = SUP_MARK + 1* and *subscr(p) = supscr(p) + 1*.

```c << Cases of |main_control| that build boxes and lists >>+=
case MMODE + SUB_MARK:
case MMODE + SUP_MARK:
    sub_sup();
    break;
```
