# Section 164

```c << Initialize table entries (done by INITEX only) >>=
for(k = MEM_BOT + 1; k <= LO_MEM_STAT_MAX; k++) {
    mem[k].sc = 0; // all glue dimensions are zeroed
}
k = MEM_BOT;
while (k <= LO_MEM_STAT_MAX) {
    // set first words of glue specifications
    glue_ref_count(k) = null + 1;
    stretch_order(k) = NORMAL;
    shrink_order(k) = NORMAL;
    k += GLUE_SPEC_SIZE;
}

stretch(FIL_GLUE) = UNITY;
stretch_order(FIL_GLUE) = FIL;

stretch(FILL_GLUE) = UNITY;
stretch_order(FILL_GLUE) = FILL;

stretch(SS_GLUE) = UNITY;
stretch_order(SS_GLUE) = FIL;

shrink(SS_GLUE) = UNITY;
shrink_order(SS_GLUE) = FIL;

stretch(FIL_NEG_GLUE) = -UNITY;
stretch_order(FIL_NEG_GLUE) = FIL;

// now initialize the dynamic memory
rover = LO_MEM_STAT_MAX + 1;
link(rover) = EMPTY_FLAG;
// which is a 1000-word available node
node_size(rover) = 1000;
llink(rover) = rover;
rlink(rover) = rover;
lo_mem_max = rover + 1000;
link(lo_mem_max) = null;
info(lo_mem_max) = null;

for(k = HI_MEM_STAT_MIN; k <= MEM_TOP; k++) {
    mem[k] = mem[lo_mem_max]; // clear list heads
}

// << Initialize the special list heads and constant nodes >>

// initialize the one-word memory
avail = null;
mem_end = MEM_TOP;
hi_mem_min = HI_MEM_STAT_MIN;
// initialize statistics
var_used = LO_MEM_STAT_MAX + 1 - MEM_BOT;
dyn_used = HI_MEM_STAT_USAGE;
```
