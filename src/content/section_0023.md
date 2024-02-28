# Section 23

The ASCII code is "standard" only to a certain extent, since many computer installations have found it advantageous to have ready access to more than 94 printing characters.
Appendix&nbsp;C of *The TeXbook* gives a complete specification of the intended correspondence between characters and $\TeX$'s internal representation.

If $\TeX$ is being used on a garden-variety Pascal for which only standard ASCII codes will appear in the input and output files, it doesn't really matter what codes are specified in *XCHR[0 .. 31]*, but the safest policy is to blank everything out by using the code shown below.

However, other settings of *XCHR* will make $\TeX$ more friendly on computers that have an extended character set, so that users can type things like '$\ne$' instead of '`\ne`'.
People with extended character sets can assign codes arbitrarily, giving an *XCHR* equivalent to whatever characters the users of $\TeX$ are allowed to have in their input files.
It is best to make the codes correspond to the intended interpretations as shown in Appendix&nbsp;C whenever possible; but this is not necessary.
For example, in countries with an alphabet of more than 26 letters, it is usually best to map the additional letters into codes less than&nbsp;32.
To get the most "permissive" character set, change '␣' on the right of these assignment statements to *chr(i)*.

> ![NOTE]
> Spaces are included in the table *XCHR* at declaration in section [20](./part02.md#section-20).
