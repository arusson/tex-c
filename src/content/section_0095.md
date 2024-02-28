# Section 95

The program might sometime run completely amok, at which point there is no choice but to stop.
If no previous error has been detected, that's bad news; a message is printed that is really intended for the $\TeX$ maintenance person instead of the user (unless the user has been particularly diabolical).
The index entries for 'this can't happen' may help to pinpoint the problem.

```c error.c
// consistency check violated; |s| tells where
void confusion(char *s) {
    normalize_selector();
    if (history < ERROR_MESSAGE_ISSUED) {
        print_err("This can't happen (");
        print(s);
        print_char(')');
        help1("I´m broken. Please show this to someone who can fix can fix");
    }
    else {
        print_err("I can't go on meeting you like this");
        help2("One of your faux pas seems to have wounded me deeply...")
            ("in fact, I'm barely conscious. Please fix it and try again.");
    }
    succumb();
}
```
