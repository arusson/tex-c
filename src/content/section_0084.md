# Section 84

It is desirable to provide an '`E`' option here that gives the user an easy way to return from $\TeX$ to the system editor, with the offending line ready to be edited.
But such an extension requires some system wizardry, so the present implementation simply types out the name of the file that should be edited and the relevant line number.

There is a secret '`D`' option available when the debugging routines haven't been commented~out.

> ![NOTE]
> No 'E' option: input edition not supported.

```c << Interpret code |c| and |return| if done >>=
switch(c) {
case '0':
case '1':
case '2':
case '3':
case '4':
case '5':
case '7':
case '8':
case '9':
    if (deletions_allowed) {
        // << Delete |c - '0'| tokens and |goto continue| >>
    }
    break;

#ifdef DEBUG
case 'D':
    debug_help();
    continue;
#endif

case 'H':
    // << Print the help information and |goto continue| >>
    break;

case 'I':
    // << Introduce new material from the terminal and |return| >>
    break;

case 'Q':
case 'R':
case 'S':
    // << Change the interaction level and |return| >>
    break;

case 'X':
    interaction = SCROLL_MODE;
    jump_out();

default:
    do_nothing;
}
// << Print the menu of available options >>
```
