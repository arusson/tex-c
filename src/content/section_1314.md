# Section 1314

```c << Undump the table of equivalents >>=
// << Undump regions 1 to 6 of |eqtb| >>
undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, par_loc);
par_token = CS_TOKEN_FLAG + par_loc;
undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, write_loc);
// << Undump the hash table >>
```
