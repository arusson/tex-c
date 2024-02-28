# Section 769

We have mentioned that alignrecords contain no *height* or *depth* fields.
Their *glue_sign* and *glue_order* are pre-empted as well, since it is necessary to store information about what to do when a template ends.
This information is called the *extra_info* field.

```c include/alignment.h
// << Start file |alignment.h| >>

#define u_part(X)     mem[(X) + HEIGHT_OFFSET].integer // pointer to <u_j> token list
#define v_part(X)     mem[(X) + DEPTH_OFFSET].integer  // pointer to <v_j> token list
#define extra_info(X) info(X + LIST_OFFSET)            // info to remember during template
```
