# Section 1208: Mode-independent processing

The long *main_control* procedure has now been fully specified, except for certain activities that are independent of the current mode.
These activities do not change the current vlist or hlist or mlist; if they change anything, it is the value of a parameter or the meaning of a control sequence.

Assignments to values in *eqtb* can be global or local.
Furthermore, a control sequence can be defined to be '`\long`' or '`\outer`', and it might or might not be expanded.
The prefixes '`\global`', '`\long`', and '`\outer`' can occur in any order.
Therefore we assign binary numeric codes, making it possible to accumulate the union of all specified prefixes by adding the corresponding codes.
(Pascal's **set** operations could also have been used.)

```c << Put each of TeX's primitives into the hash table >>+=
primitive("long", PREFIX, 1);
primitive("outer", PREFIX, 2);
primitive("global", PREFIX, 4);
primitive("def", DEF, 0);
primitive("gdef", DEF, 1);
primitive("edef", DEF, 2);
primitive("xdef", DEF, 3);
```
