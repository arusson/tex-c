# Section 501

```c << Either process \ifcase or set |b| to the value of a boolean condition >>=
switch (this_if) {
case IF_CHAR_CODE:
case IF_CAT_CODE:
    // << Test if two characters match >>
    break;

case IF_INT_CODE:
case IF_DIM_CODE:
    // << Test relation between integers or dimensions >>
    break;

case IF_ODD_CODE:
    // << Test if an integer is odd >>
    break;

case IF_VMODE_CODE:
    b = (abs(mode) == VMODE);
    break;

case IF_HMODE_CODE:
    b = (abs(mode) == HMODE);
    break;

case IF_MMODE_CODE:
    b = (abs(mode) == MMODE);
    break;

case IF_INNER_CODE:
    b = (mode < 0);
    break;

case IF_VOID_CODE:
case IF_HBOX_CODE:
case IF_VBOX_CODE:
    // << Test box register status >>
    break;

case IFX_CODE:
    // << Test if two tokens match >>
    break;

case IF_EOF_CODE:
    scan_four_bit_int();
    b = (read_open[cur_val] == CLOSED);
    break;

case IF_TRUE_CODE:
    b = true;
    break;

case IF_FALSE_CODE:
    b = false;
    break;

case IF_CASE_CODE:
    // << Select the appropriate case and |return| or |goto common_ending| >>
} // there are no other cases
```
