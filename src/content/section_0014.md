# Section 14

Later on we will say '**if** *MEM_MAX* $\geq$ *MAX_HALFWORD* **then** *bad* &larr; 14', or something similar.
(We can't do that until *MAX_HALFWORD* has been defined.)

```c << Check the "constant" values for consistency >>=
bad = 0;
if (HALF_ERROR_LINE < 30 || HALF_ERROR_LINE > ERROR_LINE - 15) {
    bad = 1;
}
if (MAX_PRINT_LINE < 60) {
    bad = 2;
}
if (DVI_BUF_SIZE % 8 != 0) {
    bad = 3;
}
if (MEM_BOT + 1100 > MEM_TOP) {
    bad = 4;
}
if (HASH_PRIME > HASH_SIZE) {
    bad = 5;
}
if (MAX_IN_OPEN >= 128) {
    bad = 6;
}
if (MEM_TOP < 256 + 11) {
    bad = 7; // we will want |NULL_LIST > 255|
}
```
