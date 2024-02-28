# Section 411

The hash table is initialized with '`\count`', '`\dimen`', '`\skip`', and '`\muskip`' all having *REGISTER* as their command code; they are distinguished by the *chr_code*, which is either *INT_VAL*, *DIMEN_VAL*, *GLUE_VAL*, or *MU_VAL*.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("count", REGISTER, INT_VAL);
primitive("dimen", REGISTER, DIMEN_VAL);
primitive("skip", REGISTER, GLUE_VAL);
primitive("muskip", REGISTER, MU_VAL);
```
