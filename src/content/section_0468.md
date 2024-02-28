# Section 468

The primitives `\number`, `\romannumeral`, `\string`, `\meaning`, `\fontname`, and `\jobname` are defined as follows.

```c include/constants.h
#define NUMBER_CODE        0 // command code for \number
#define ROMAN_NUMERAL_CODE 1 // command code for \romannumeral
#define STRING_CODE        2 // command code for \string
#define MEANING_CODE       3 // command code for \meaning
#define FONT_NAME_CODE     4 // command code for \fontname
#define JOB_NAME_CODE      5 // command code for \jobname
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("number", CONVERT, NUMBER_CODE);
primitive("romannumeral", CONVERT, ROMAN_NUMERAL_CODE);
primitive("string", CONVERT, STRING_CODE);
primitive("meaning", CONVERT, MEANING_CODE);
primitive("fontname", CONVERT, FONT_NAME_CODE);
primitive("jobname", CONVERT, JOB_NAME_CODE);
```
