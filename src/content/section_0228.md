# Section 228

All glue parameters and registers are initially '`0pt plus0pt minus0pt`'.

```c << Initialize table entries (done by INITEX only) >>+=
equiv(GLUE_BASE) = ZERO_GLUE;
eq_level(GLUE_BASE) = LEVEL_ONE;
eq_type(GLUE_BASE) = GLUE_REF;
for(k = GLUE_BASE + 1; k < LOCAL_BASE; k++) {
    eqtb[k] = eqtb[GLUE_BASE];
}
glue_ref_count(ZERO_GLUE) += LOCAL_BASE - GLUE_BASE;
```
