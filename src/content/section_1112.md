# Section 1112

Italic corrections are converted to kern nodes when the *ITAL_CORR* command follows a character.
In math mode the same effect is achieved by appending a kern of zero here, since italic corrections are supplied later.

```c << Cases of |main_control| that build boxes and lists >>+=
case HMODE + ITAL_CORR:
    append_italic_correction();
    break;

case MMODE + ITAL_CORR:
    tail_append(new_kern(0));
    break;
```
