# Section 566

The preliminary settings of the index-offset variables *char_base*, *width_base*, *lig_kern_base*, *kern_base*, and *exten_base* will be corrected later by subtracting *MIN_QUARTERWORD* from them; and we will subtract 1 from *param_base* too.
It's best to forget about such anomalies until later.

```c << Use size fields to allocate font information >>=
lf = lf - 6 - lh; // |lf| words should be loaded into |font_info|
if (np < 7) {
    lf += 7 - np; // at least seven parameters will appear
}
if (font_ptr == FONT_MAX || fmem_ptr + lf > FONT_MEM_SIZE) {
    // << Apologize for not loading the font, |goto done| >>
}
f = font_ptr + 1;
char_base[f] = fmem_ptr - bc;
width_base[f] = char_base[f] + ec + 1;
height_base[f] = width_base[f] + nw;
depth_base[f] = height_base[f] + nh;
italic_base[f] = depth_base[f] + nd;
lig_kern_base[f] = italic_base[f] + ni;
kern_base[f] = lig_kern_base[f] + nl - KERN_BASE_OFFSET;
exten_base[f] = kern_base[f] + KERN_BASE_OFFSET + nk;
param_base[f] = exten_base[f] + ne;
```
