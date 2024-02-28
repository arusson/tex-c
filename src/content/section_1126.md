# Section 1126

When '`\cr`' or '`\span`' or a tab mark comes through the scanner into *main_control*, it might be that the user has foolishly inserted one of them into something that has nothing to do with alignment.
But it is far more likely that a left brace or right brace has been omitted, since *get_next* takes actions appropriate to alignment only when '`\cr`' or '`\span`' or tab marks occur with *align_state = 0*.
The following program attempts to make an appropriate recovery.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(CAR_RET):
any_mode(TAB_MARK):
    align_error();
    break;

any_mode(NO_ALIGN):
    no_align_error();
    break;

any_mode(OMIT):
    omit_error();
    break;
```
