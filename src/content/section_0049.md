# Section 49

The first 128 strings will contain 95 standard ASCII characters, and the other 33 characters will be printed in three-symbol form like '`^^A`' unless a system-dependent change is made here. Installations that have an extended character set, where for example *XCHR[26]* = '`≠`', would like string 26 to be the single character 26 instead of the three characters 94, 94, 90 (`^^Z`).
On the other hand, even people with an extended character set will want to represent string 13 by `^^M`, since 13 is *CARRIAGE_RETURN*;
the idea is to produce visible strings instead of tabs or line-feeds or carriage-returns or bell-rings or characters that are treated anomalously in text files.

Unprintable characters of codes 128--255 are, similarly, rendered `^^80`--`^^ff`.

The boolean expression defined here should be *true* unless $\TeX$ internal code number *k* corresponds to a non-troublesome visible symbol in the local character set.
An appropriate formula for the extended character set recommended in *The TeXbook* would, for example, be *k* $\in$ *[0, 8 .. 10, 12, 13, 27, 127 .. 255]*.
If character *k* cannot be printed, and *k* $<$ *128*, then character *k* + 64 or *k − 64* must be printable;
moreover, ASCII codes *[33 .. 38, 48 .. 57, 94, 97 .. 102, 112 .. 121]* must be printable.
Thus, at least 80 printable characters are needed.

> ![NOTE]
> The condition ⟨&nbsp;Character |k| cannot be printed, 49&nbsp;⟩ is already included in section [48](./part04.md#section-48).
