# Section 1210

Every prefix, and every command code that might or might not be prefixed, calls the action procedure *prefixed_command*.
This routine accumulates a sequence of prefixes until coming to a non-prefix, then it carries out the command.

```c << Cases of |main_control| that don't depend on |mode| >>=
any_mode(TOKS_REGISTER):
any_mode(ASSIGN_TOKS):
any_mode(ASSIGN_INT):
any_mode(ASSIGN_DIMEN):
any_mode(ASSIGN_GLUE):
any_mode(ASSIGN_MU_GLUE):
any_mode(ASSIGN_FONT_DIMEN):
any_mode(ASSIGN_FONT_INT):
any_mode(SET_AUX):
any_mode(SET_PREV_GRAF):
any_mode(SET_PAGE_DIMEN):
any_mode(SET_PAGE_INT):
any_mode(SET_BOX_DIMEN):
any_mode(SET_SHAPE):
any_mode(DEF_CODE):
any_mode(DEF_FAMILY):
any_mode(SET_FONT):
any_mode(DEF_FONT):
any_mode(REGISTER):
any_mode(ADVANCE):
any_mode(MULTIPLY):
any_mode(DIVIDE):
any_mode(PREFIX):
any_mode(LET):
any_mode(SHORTHAND_DEF):
any_mode(READ_TO_CS):
any_mode(DEF):
any_mode(SET_BOX):
any_mode(HYPH_DATA):
any_mode(SET_INTERACTION):
    prefixed_command();
    break;
```
