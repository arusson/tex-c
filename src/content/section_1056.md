# Section 1056

As an introduction to these routines, let's consider one of the simplest cases:
What happens when '`\hrule`' occurs in vertical mode, or '`\vrule`' in horizontal mode or math mode? The code in *main_control*
is short, since the *scan_rule_spec* routine already does most of what is required; thus, there is no need for a special action procedure.

Note that baselineskip calculations are disabled after a rule in vertical mode, by setting *prev_depth = IGNORE_DEPTH*.

```c << Cases of |main_control| that build boxes and lists >>=
case VMODE + HRULE:
case HMODE + VRULE:
case MMODE + VRULE:
    tail_append(scan_rule_spec());
    if (abs(mode) == VMODE) {
        prev_depth = IGNORE_DEPTH;
    }
    else if (abs(mode) == HMODE) {
        space_factor = 1000;
    }
    break;
```
