# Section 1063

If a left brace occurs in the middle of a page or paragraph, it simply introduces a new level of grouping, and the matching right brace will not have such a drastic effect.
Such grouping affects neither the mode nor the current list.

```c << Cases of |main_control| that build boxes and lists >>+=
non_math(LEFT_BRACE):
    new_save_level(SIMPLE_GROUP);
    break;

any_mode(BEGIN_GROUP):
    new_save_level(SEMI_SIMPLE_GROUP);
    break;

any_mode(END_GROUP):
    if (cur_group == SEMI_SIMPLE_GROUP) {
        unsave();
    }
    else {
        off_save();
    }
    break;
```
