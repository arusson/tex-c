# Section 79

Individual lines of help are recorded in the array *help_line*, which contains entries in positions *0 .. (help_ptr − 1)*.
They should be printed in reverse order, i.e., with *help_line[0]* appearing last.

```c include/texerror.h
#define hlp1(X) help_line[0] = (X)
#define hlp2(X) help_line[1] = (X); hlp1
#define hlp3(X) help_line[2] = (X); hlp2
#define hlp4(X) help_line[3] = (X); hlp3
#define hlp5(X) help_line[4] = (X); hlp4
#define hlp6(X) help_line[5] = (X); hlp5
#define help0   help_ptr = 0       // sometimes there might be no help
#define help1   help_ptr = 1; hlp1 // use this with one help line
#define help2   help_ptr = 2; hlp2 // use this with two help lines
#define help3   help_ptr = 3; hlp3 // use this with three help lines
#define help4   help_ptr = 4; hlp4 // use this with four help lines
#define help5   help_ptr = 5; hlp5 // use this with five help lines
#define help6   help_ptr = 6; hlp6 // use this with six help lines
```

```c << Global variables >>+=
char *help_line[6]; // helps for the next |error|
int help_ptr;       // the number of help lines present
bool use_err_help;  // should the |err_help| list be shown?
```
