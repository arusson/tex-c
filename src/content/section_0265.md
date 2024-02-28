# Section 265

Many of $\TeX$'s primitives need no *equiv*, since they are identifiable by their *eq_type* alone.
These primitives are loaded into the hash table as follows:

```c << Put each of TeX's primitives into the hash table >>+=
primitive(" ", EX_SPACE, 0);
primitive("/", ITAL_CORR, 0);
primitive("accent", ACCENT, 0);
primitive("advance", ADVANCE, 0);
primitive("afterassignment", AFTER_ASSIGNMENT, 0);
primitive("aftergroup", AFTER_GROUP, 0);
primitive("begingroup", BEGIN_GROUP, 0);
primitive("char", CHAR_NUM, 0);
primitive("csname", CS_NAME, 0);
primitive("delimiter", DELIM_NUM, 0);
primitive("divide", DIVIDE, 0);
primitive("endcsname", END_CS_NAME, 0);
primitive("endgroup", END_GROUP, 0);
text(FROZEN_END_GROUP) = str_ptr - 1; // "endgroup"
eqtb[FROZEN_END_GROUP] = eqtb[cur_val];

primitive("expandafter", EXPAND_AFTER, 0);
primitive("font", DEF_FONT, 0);
primitive("fontdimen", ASSIGN_FONT_DIMEN, 0);
primitive("halign", HALIGN, 0);
primitive("hrule", HRULE, 0);
primitive("ignorespaces", IGNORE_SPACES, 0);
primitive("insert", INSERT, 0);
primitive("mark", MARK, 0);
primitive("mathaccent", MATH_ACCENT, 0);
primitive("mathchar", MATH_CHAR_NUM, 0);
primitive("mathchoice", MATH_CHOICE, 0);
primitive("multiply", MULTIPLY, 0);
primitive("noalign", NO_ALIGN, 0);
primitive("noboundary", NO_BOUNDARY, 0);
primitive("noexpand", NO_EXPAND, 0);
primitive("nonscript", NON_SCRIPT, 0);
primitive("omit", OMIT, 0);
primitive("parshape", SET_SHAPE, 0);
primitive("penalty", BREAK_PENALTY, 0);
primitive("prevgraf", SET_PREV_GRAF, 0);
primitive("radical", RADICAL, 0);
primitive("read", READ_TO_CS, 0);
primitive("relax", RELAX, 256); // cf. |scan_file_name|
text(FROZEN_RELAX) = str_ptr - 1; // "relax"
eqtb[FROZEN_RELAX] = eqtb[cur_val];

primitive("setbox", SET_BOX, 0);
primitive("the", THE, 0);
primitive("toks", TOKS_REGISTER, 0);
primitive("vadjust", VADJUST, 0);
primitive("valign", VALIGN, 0);
primitive("vcenter", VCENTER, 0);
primitive("vrule", VRULE, 0);
```
