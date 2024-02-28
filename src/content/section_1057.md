# Section 1057

The processing of things like `\hskip` and `\vskip` is slightly more complicated.
But the code in *main_control* is very short, since it simply calls on the action routine *append_glue*.
Similarly, `\kern` activates *append_kern*.

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + VSKIP:
case HMODE + HSKIP:
case MMODE + HSKIP:
case MMODE + MSKIP:
    append_glue();
    break;

any_mode(KERN):
case MMODE + MKERN:
    append_kern();
    break;
```
