# Section 463

Here's a similar procedure that returns a pointer to a rule node.
This routine is called just after $\TeX$ has seen `\hrule` or `\vrule`;
therefore *cur_cmd* will be either *hrule* or *vrule*.
The idea is to store the default rule dimensions in the node, then to override them if
'`height`' or '`width`' or '`depth`' specifications are found (in any order).

```c include/constants.h
#define DEFAULT_RULE 26214 // 0.4 pt
```

```c parser/subroutines.c
pointer scan_rule_spec() {
    pointer q; // the rule node being created
    q = new_rule(); // |width|, |depth|, and |height| all equal |NULL_FLAG| now
    if (cur_cmd == VRULE) {
        width(q) = DEFAULT_RULE;
    }
    else {
        height(q) = DEFAULT_RULE;
        depth(q) = 0;
    }
reswitch:
    if (scan_keyword("width")) {
        scan_normal_dimen;
        width(q) = cur_val;
        goto reswitch;
    }
    if (scan_keyword("height")) {
        scan_normal_dimen;
        height(q) = cur_val;
        goto reswitch;
    }
    if (scan_keyword("depth")) {
        scan_normal_dimen;
        depth(q) = cur_val;
        goto reswitch;
    }
    return q;
}
```
