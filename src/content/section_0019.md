# Section 19

The original Pascal compiler was designed in the late 60s, when six-bit character sets were common, so it did not make provision for lowercase letters.
Nowadays, of course, we need to deal with both capital and small letters in a convenient way, especially in a program for typesetting;
so the present specification of $\TeX$ has been written under the assumption that the Pascal compiler and run-time system permit the use of text files with more than 64 distinguishable characters.
More precisely, we assume that the character set contains at least the letters and symbols associated with ASCII codes 32 through 126; all of these characters are now available on most computer terminals.

Since we are dealing with more characters than were present in the first Pascal compilers, we have to decide what to call the associated data type.
Some Pascals use the original name *char* for the characters in text files, even though there now are more than 64 such characters, while other Pascals consider *char* to be a 64-element subrange of a larger data type that has some other name.

In order to accommodate this difference, we shall use the name *text_char* to stand for the data type of the characters that are converted to and from *ASCII_code* when they are input and output.
We shall also assume that *text_char* consists of the elements *chr(FIRST_TEXT_CHAR)* through *chr(LAST_TEXT_CHAR)*, inclusive.
The following definitions should be adjusted if necessary.

> ![NOTE]
> *text_char* is not kept.

```c include/constants.h
#define FIRST_TEXT_CHAR 0   // ordinal number of the smallest element of |text_char|
#define LAST_TEXT_CHAR  255 // ordinal number of the largest element of |text_char|
```

```c << Local variables for initialization >>=
// int i; no used
```
