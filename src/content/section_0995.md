# Section 995

```c include/builder.h
#define contrib_tail nest[0].tail_field // tail of the contribution list
```

```c << Make the contribution list empty by setting its tail to |CONTRIB_HEAD| >>=
if (nest_ptr == 0) {
    tail = CONTRIB_HEAD; // vertical mode
}
else {
    contrib_tail = CONTRIB_HEAD; // other modes
}
```
