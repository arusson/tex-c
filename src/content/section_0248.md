# Section 248

```c << Put each of TeX's primitives into the hash table >>+=
primitive("parindent", ASSIGN_DIMEN, DIMEN_BASE + PAR_INDENT_CODE);
primitive("mathsurround", ASSIGN_DIMEN, DIMEN_BASE + MATH_SURROUND_CODE);
primitive("lineskiplimit", ASSIGN_DIMEN, DIMEN_BASE + LINE_SKIP_LIMIT_CODE);
primitive("hsize", ASSIGN_DIMEN, DIMEN_BASE + HSIZE_CODE);
primitive("vsize", ASSIGN_DIMEN, DIMEN_BASE + VSIZE_CODE);
primitive("maxdepth", ASSIGN_DIMEN, DIMEN_BASE + MAX_DEPTH_CODE);
primitive("splitmaxdepth", ASSIGN_DIMEN, DIMEN_BASE + SPLIT_MAX_DEPTH_CODE);
primitive("boxmaxdepth", ASSIGN_DIMEN, DIMEN_BASE + BOX_MAX_DEPTH_CODE);
primitive("hfuzz", ASSIGN_DIMEN, DIMEN_BASE + HFUZZ_CODE);
primitive("vfuzz", ASSIGN_DIMEN, DIMEN_BASE + VFUZZ_CODE);
primitive("delimitershortfall", ASSIGN_DIMEN, DIMEN_BASE + DELIMITER_SHORTFALL_CODE);
primitive("nulldelimiterspace", ASSIGN_DIMEN, DIMEN_BASE + NULL_DELIMITER_SPACE_CODE);
primitive("scriptspace", ASSIGN_DIMEN, DIMEN_BASE + SCRIPT_SPACE_CODE);
primitive("predisplaysize", ASSIGN_DIMEN, DIMEN_BASE + PRE_DISPLAY_SIZE_CODE);
primitive("displaywidth", ASSIGN_DIMEN, DIMEN_BASE + DISPLAY_WIDTH_CODE);
primitive("displayindent", ASSIGN_DIMEN, DIMEN_BASE + DISPLAY_INDENT_CODE);
primitive("overfullrule", ASSIGN_DIMEN, DIMEN_BASE + OVERFULL_RULE_CODE);
primitive("hangindent", ASSIGN_DIMEN, DIMEN_BASE + HANG_INDENT_CODE);
primitive("hoffset", ASSIGN_DIMEN, DIMEN_BASE + H_OFFSET_CODE);
primitive("voffset", ASSIGN_DIMEN, DIMEN_BASE + V_OFFSET_CODE);
primitive("emergencystretch", ASSIGN_DIMEN, DIMEN_BASE + EMERGENCY_STRETCH_CODE);
```
