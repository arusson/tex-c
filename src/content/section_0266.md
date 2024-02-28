# Section 266

Each primitive has a corresponding inverse, so that it is possible to display the cryptic numeric contents of *eqtb* in symbolic form.
Every call of *primitive* in this program is therefore accompanied by some straightforward code that forms part of the *print_cmd_chr* routine below.

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ACCENT:
    print_esc("accent");
    break;

case ADVANCE:
    print_esc("advance");
    break;

case AFTER_ASSIGNMENT:
    print_esc("afterassignment");
    break;

case AFTER_GROUP:
    print_esc("aftergroup");
    break;

case ASSIGN_FONT_DIMEN:
    print_esc("fontdimen");
    break;

case BEGIN_GROUP:
    print_esc("begingroup");
    break;

case BREAK_PENALTY:
    print_esc("penalty");
    break;

case CHAR_NUM:
    print_esc("char");
    break;

case CS_NAME:
    print_esc("csname");
    break;

case DEF_FONT:
    print_esc("font");
    break;

case DELIM_NUM:
    print_esc("delimiter");
    break;

case DIVIDE:
    print_esc("divide");
    break;

case END_CS_NAME:
    print_esc("endcsname");
    break;

case END_GROUP:
    print_esc("endgroup");
    break;

case EX_SPACE:
    print_esc(" ");
    break;

case EXPAND_AFTER:
    print_esc("expandafter");
    break;

case HALIGN:
    print_esc("halign");
    break;

case HRULE:
    print_esc("hrule");
    break;

case IGNORE_SPACES:
    print_esc("ignorespaces");
    break;

case INSERT:
    print_esc("insert");
    break;

case ITAL_CORR:
    print_esc("/");
    break;

case MARK:
    print_esc("mark");
    break;

case MATH_ACCENT:
    print_esc("mathaccent");
    break;

case MATH_CHAR_NUM:
    print_esc("mathchar");
    break;

case MATH_CHOICE:
    print_esc("mathchoice");
    break;

case MULTIPLY:
    print_esc("multiply");
    break;

case NO_ALIGN:
    print_esc("noalign");
    break;

case NO_BOUNDARY:
    print_esc("noboundary");
    break;

case NO_EXPAND:
    print_esc("noexpand");
    break;

case NON_SCRIPT:
    print_esc("nonscript");
    break;

case OMIT:
    print_esc("omit");
    break;

case RADICAL:
    print_esc("radical");
    break;

case READ_TO_CS:
    print_esc("read");
    break;

case RELAX:
    print_esc("relax");
    break;

case SET_BOX:
    print_esc("setbox");
    break;

case SET_PREV_GRAF:
    print_esc("prevgraf");
    break;

case SET_SHAPE:
    print_esc("parshape");
    break;

case THE:
    print_esc("the");
    break;

case TOKS_REGISTER:
    print_esc("toks");
    break;

case VADJUST:
    print_esc("vadjust");
    break;

case VALIGN:
    print_esc("valign");
    break;

case VCENTER:
    print_esc("vcenter");
    break;

case VRULE:
    print_esc("vrule");
    break;
```
