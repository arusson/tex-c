# Section 314

```c << Print type of token list >>=
switch (token_type) {
case PARAMETER:
    print_nl("<argument> ");
    break;

case U_TEMPLATE:
case V_TEMPLATE:
    print_nl("<template> ");
    break;

case BACKED_UP:
    if (loc == null) {
        print_nl("<recently read> ");
    }
    else {
        print_nl("<to be read again> ");
    }
    break;

case INSERTED:
    print_nl("<inserted text> ");
    break;

case MACRO:
    print_ln();
    print_cs(name);
    break;

case OUTPUT_TEXT:
    print_nl("<output> ");
    break;

case EVERY_PAR_TEXT:
    print_nl("<everypar> ");
    break;

case EVERY_MATH_TEXT:
    print_nl("<everymath> ");
    break;

case EVERY_DISPLAY_TEXT:
    print_nl("<everydisplay> ");
    break;

case EVERY_HBOX_TEXT:
    print_nl("<everyhbox> ");
    break;

case EVERY_VBOX_TEXT:
    print_nl("<everyvbox> ");
    break;

case EVERY_JOB_TEXT:
    print_nl("<everyjob> ");
    break;

case EVERY_CR_TEXT:
    print_nl("<everycr> ");
    break;

case MARK_TEXT:
    print_nl("<mark> ");
    break;

case WRITE_TEXT:
    print_nl("<write> ");
    break;

default:
    print_nl("?"); // this should never happen
}
```
