# Section 2

The present implementation has a long ancestry, beginning in the summer of&nbsp;1977, when Michael&nbsp;F. Plass and Frank&nbsp;M. Liang designed and coded a prototype based on some specifications that the author had made in May of that year.
This original proto$\TeX$ included macro definitions and elementary manipulations on boxes and glue, but it did not have line-breaking, page-breaking, mathematical formulas, alignment routines, error recovery, or the present semantic nest; furthermore, it used character lists instead of token lists, so that a control sequence like `\halign` was represented by a list of seven characters.
A complete version of $\TeX$ was designed and coded by the author in late 1977 and early 1978; that program, like its prototype, was written in the SAIL language, for which an excellent debugging system was available.
Preliminary plans to convert the SAIL code into a form somewhat like the present "web" were developed by Luis Trabb&nbsp;Pardo and the author at the beginning of 1979, and a complete implementation was created by Ignacio&nbsp;A. Zabala in 1979 and 1980.
The $\TeX82$ program, which was written by the author during the latter part of 1981 and the early part of 1982, also incorporates ideas from the 1979 implementation of $\TeX$ in MESA that was written by Leonidas Guibas, Robert Sedgewick, and Douglas Wyatt at the Xerox Palo Alto Research Center.
Several hundred refinements were introduced into $\TeX82$ based on the experiences gained with the original implementations, so that essentially every part of the system has been substantially improved.
After the appearance of "Version 0" in September 1982, this program benefited greatly from the comments of many other people, notably David&nbsp;R. Fuchs and Howard&nbsp;W. Trickey.
A final revision in September 1989 extended the input character set to eight-bit codes and introduced the ability to hyphenate words from different languages, based on some ideas of Michael&nbsp;J. Ferguson.

No doubt there still is plenty of room for improvement, but the author is firmly committed to keeping $\TeX82$ "frozen" from now on; stability and reliability are to be its main virtues.

On the other hand, the `WEB` description can be extended without changing the core of $\TeX82$ itself, and the program has been designed so that such extensions are not extremely difficult to make.
The *BANNER* string defined here should be changed whenever $\TeX$ undergoes any modifications, so that it will be clear which version of $\TeX$ might be the guilty party when a problem arises.

If this program is changed, the resulting system should not be called '$\TeX$'; the official name '$\TeX$' by itself is reserved for software systems that are fully compatible with each other.
A special test suite called the "`TRIP` test" is available for helping to determine whether a particular implementation deserves to be known as '$\TeX$' [cf.&nbsp;Stanford Computer Science report CS1027, November 1984].

> ![NOTE]
> Constants are written in capital letters.
> 
> This C implementation passes the `TRIP` test, and did not change anything of the core of $\TeX$ so it can be called $\TeX$.


```c include/constants.h
// << Start file |constants.h| >>

#define BANNER "This is TeX, Version 3.141592653" // printed when TeX starts
```


