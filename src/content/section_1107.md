# Section 1107

```c << Put each of TeX's primitives into the hash table >>+=
primitive("unpenalty", REMOVE_ITEM, PENALTY_NODE);
primitive("unkern", REMOVE_ITEM, KERN_NODE);
primitive("unskip", REMOVE_ITEM, GLUE_NODE);
primitive("unhbox", UN_HBOX, BOX_CODE);
primitive("unhcopy", UN_HBOX, COPY_CODE);
primitive("unvbox", UN_VBOX, BOX_CODE);
primitive("unvcopy", UN_VBOX, COPY_CODE);
```
