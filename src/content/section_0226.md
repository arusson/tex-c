# Section 226

The symbolic names for glue parameters are put into $\TeX$'s hash table by using the routine called *primitive*, defined below.
Let us enter them now, so that we don't have to list all those parameter names anywhere else.

```c << Put each of TeX's primitives into the hash table >>=
primitive("lineskip", ASSIGN_GLUE, GLUE_BASE + LINE_SKIP_CODE);
primitive("baselineskip", ASSIGN_GLUE, GLUE_BASE + BASELINE_SKIP_CODE);
primitive("parskip", ASSIGN_GLUE, GLUE_BASE + PAR_SKIP_CODE);
primitive("abovedisplayskip", ASSIGN_GLUE, GLUE_BASE + ABOVE_DISPLAY_SKIP_CODE);
primitive("belowdisplayskip", ASSIGN_GLUE, GLUE_BASE + BELOW_DISPLAY_SKIP_CODE);
primitive("abovedisplayshortskip",  ASSIGN_GLUE, GLUE_BASE + ABOVE_DISPLAY_SHORT_SKIP_CODE);
primitive("belowdisplayshortskip",  ASSIGN_GLUE, GLUE_BASE + BELOW_DISPLAY_SHORT_SKIP_CODE);
primitive("leftskip", ASSIGN_GLUE, GLUE_BASE + LEFT_SKIP_CODE);
primitive("rightskip", ASSIGN_GLUE, GLUE_BASE + RIGHT_SKIP_CODE);
primitive("topskip", ASSIGN_GLUE, GLUE_BASE + TOP_SKIP_CODE);
primitive("splittopskip", ASSIGN_GLUE, GLUE_BASE + SPLIT_TOP_SKIP_CODE);
primitive("tabskip", ASSIGN_GLUE, GLUE_BASE + TAB_SKIP_CODE);
primitive("spaceskip", ASSIGN_GLUE, GLUE_BASE + SPACE_SKIP_CODE);
primitive("xspaceskip", ASSIGN_GLUE, GLUE_BASE + XSPACE_SKIP_CODE);
primitive("parfillskip", ASSIGN_GLUE, GLUE_BASE + PAR_FILL_SKIP_CODE);
primitive("thinmuskip", ASSIGN_MU_GLUE, GLUE_BASE + THIN_MU_SKIP_CODE);
primitive("medmuskip", ASSIGN_MU_GLUE, GLUE_BASE + MED_MU_SKIP_CODE);
primitive("thickmuskip", ASSIGN_MU_GLUE, GLUE_BASE + THICK_MU_SKIP_CODE);
```
