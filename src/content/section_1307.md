# Section 1307

The next few sections of the program should make it clear how we use the
dump/undump macros.

```c << Dump constants for consistency check >>=
dump_int(0);
dump_int(MEM_BOT);
dump_int(MEM_TOP);
dump_int(EQTB_SIZE);
dump_int(HASH_PRIME);
dump_int(HYPH_SIZE);
```