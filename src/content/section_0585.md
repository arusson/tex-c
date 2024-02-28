# Section 585

Here is a list of all the commands that may appear in a `DVI` file.
Each command is specified by its symbolic name (e.g., *BOP*), its opcode byte (e.g., 139), and its parameters (if any).
The parameters are followed by a bracketed number telling how many bytes they occupy;
for example, *'p[4]'* means that parameter *p* is four bytes long.

- *SET_CHAR_0* 0.<br>
  Typeset character number&nbsp;0 from font&nbsp;*f* such that the reference
  point of the character is at *(h, v)*.
  Then increase *h* by the width of that character.
  Note that a character may have zero or negative width, so one cannot be sure
  that *h* will advance after this command; but *h* usually does increase.

- *SET_CHAR_1* through *SET_CHAR_127* (opcodes 1 to 127).<br>
  Do the operations of *SET_CHAR_0*; but use the character whose number
  matches the opcode, instead of character&nbsp;0.

- *SET1* 128 *c[1]*.<br>
  Same as *SET_CHAR_0*, except that character
  number&nbsp;*c* is typeset.
  $\TeX82$ uses this command for characters in the range *128* $\leq$ *c* < *256*.

- *SET2* 129 *c[2]*.<br>
  Same as *SET1*, except that *c*&nbsp;is two bytes long, so it is in the range *0* $\leq$ *c* $<$ *65536*.
  $\TeX82$ never uses this command, but it should come in handy for extensions of $\TeX$ that deal
  with oriental languages.

- *SET3* 130 *c[3]*.<br>
  Same as *SET1*, except that *c*&nbsp;is three bytes long, so it can be as large as $2^{24} - 1$.
  Not even the Chinese language has this many characters, but this command might prove useful
  in some yet unforeseen extension.

- *SET4* 131 *c[4]*.<br>
  Same as *SET1*, except that *c*&nbsp;is four bytes long.
  Imagine that.

- *SET_RULE* 132 *a[4]* *b[4]*.<br>
  Typeset a solid black rectangle of height&nbsp;*a* and width&nbsp;*b*, with its bottom left corner at *(h, v)*.
  Then set *h &larr; h + b*.
  If either *a* $\leq$ *0* or *b* $\leq$ *0*, nothing should be typeset.
  Note that if *b* $<$ *0*, the value of *h* will decrease even though nothing else happens.
  See below for details about how to typeset rules so that consistency with `METAFONT` is guaranteed.

- *PUT1* 133 *c[1]*.<br>
  Typeset character number&nbsp;*c* from font&nbsp;*f* such that the reference point of the character is at *(h, v)*.
  (The 'PUT' commands are exactly like the 'SET' commands, except that they simply put out a
  character or a rule without moving the reference point afterwards.)

- *PUT2* 134 *c[2]*.<br>
  Same as *SET2*, except that *h* is not changed.

- *PUT3* 135 *c[3]*.<br>
  Same as *SET3*, except that *h* is not changed.

- *PUT4* 136 *c[4]*.<br>
  Same as *SET4*, except that *h* is not changed.

- *PUT_RULE* 137 *a[4]* *b[4]*.<br>
  Same as *SET_RULE*, except that *h* is not changed.

- *NOP* 138.<br>
  No operation, do nothing.
  Any number of *NOP*'s may occur between `DVI` commands, but a *NOP* cannot be inserted between
  a command and its parameters or between two parameters.

- *BOP* 139 $c_0$[4] $c_1$[4] $\ldots$ $c_9$[4] *p*[4].<br>
  Beginning of a page: Set *(h, v, w, x, y, z) &larr; (0, 0, 0, 0, 0, 0)* and set the stack empty.
  Set the current font *f* to an undefined value.
  The ten $c_i$ parameters hold the values of `\count0` $\ldots$ `\count9` in $\TeX$ at the time
  `\shipout` was invoked for this page; they can be used to identify
  pages, if a user wants to print only part of a `DVI` file.
  The parameter *p* points to the previous *BOP* in the file; the first
  *BOP* has *p = −1*.

- *EOP* 140.<br>
  End of page: Print what you have read since the previous *BOP*.
  At this point the stack should be empty.
  (The `DVI`-reading programs that drive most output devices will have kept a buffer of the
  material that appears on the page that has just ended.
  This material is largely, but not entirely, in order by *v* coordinate and (for fixed *v*) by
  *h*&nbsp;coordinate; so it usually needs to be sorted into some order that is
  appropriate for the device in question.)

- *PUSH* 141.<br>
  Push the current values of *(h, v, w, x, y, z)* onto the
  top of the stack; do not change any of these values.
  Note that *f* is not pushed.

- *POP* 142.<br>
  Pop the top six values off of the stack and assign them respectively to *(h, v, w, x, y, z)*.
  The number of pops should never exceed the number of pushes, since it would be highly
  embarrassing if the stack were empty at the time of a *POP* command.

- *RIGHT1* 143 *b[1]*.<br>
  Set *h &larr; h + b*, i.e., move right *b* units.
  The parameter is a signed number in two's complement notation, *−128* $\leq$ *b* $<$ *128*;
  if *b* $<$ *0*, the reference point moves left.

- *RIGHT2* 144 *b[2]*.<br>
  Same as *RIGHT1*, except that *b* is a two-byte quantity in the range *−32768* $\leq$ *b* $<$ *32768*.

- *RIGHT3* 145 *b[3]*.<br>
  Same as *RIGHT1*, except that *b* is a three-byte quantity in the range $-2^{23} \leq b < 2^{23}$.

- *RIGHT4* 146 *b[4]*.<br>
  Same as *RIGHT1*, except that *b* is a four-byte quantity in the range $-2^{31} \leq b < 2^{31}$.

- *W0* 147.<br>
  Set *h &larr; h + w*; i.e., move right *w* units.
  With luck, this parameterless command will usually suffice, because the same kind of motion
  will occur several times in succession; the following commands explain how
  *w* gets particular values.

- *W1* 148 *b[1]*.<br>
  Set *w &larr; b* and *h &larr; h + b*.
  The value of *b* is a signed quantity in two's complement notation, *−128* $\leq$ *b* $<$ *128*.
  This command changes the current *w*&nbsp;spacing and moves right by *b*.

- *W2* 149 *b[2]*.<br>
  Same as *W1*, but *b* is two bytes long, *−32768* $\leq$ *b* $<$ *32768*.

- *W3* 150 *b[3]*.<br>
  Same as *W1*, but *b* is three bytes long, $-2^{23} \leq b < 2^{23}$.

- *W4* 151 *b[4]*.<br>
  Same as *W1*, but *b* is four bytes long, $-2^{31} \leq b < 2^{31}$.

- *X0* 152.<br>
  Set *h &larr; h + x*; i.e., move right *x* units.
  The *'X'* commands are like the *'W'* commands except that they involve *x* instead of *w*.

- *X1* 153 *b[1]*.<br>
  Set *x &larr; b* and *h &larr; h + b*.
  The value of *b* is a signed quantity in two's complement notation, *−128* $\leq$ *b* $<$ *128*.
  This command changes the current *x*&nbsp;spacing and moves right by *b*.

- *X2* 154 *b[2]*.<br>
  Same as *X1*, but *b* is two bytes long, *−32768* $\leq$ *b* $<$ *32768*.

- *X3* 155 *b[3]*.<br>
  Same as *X1*, but *b* is three bytes long, $-2^{23} \leq b < 2^{23}$.

- *X4* 156 *b[4]*.<br>
  Same as *X1*, but *b* is four bytes long, $-2^{31} \leq b < 2^{31}$.

- *DOWN1* 157 *a[1]*.<br>
  Set *v &larr; v + a*, i.e., move down *a* units.
  The parameter is a signed number in two's complement notation, *−128* $\leq$ *a* $<$ *128*;
  if *a* $<$ *0*, the reference point moves up.

- *DOWN2* 158 *a[2]*.<br>
  Same as *DOWN1*, except that *a* is a two-byte quantity in the range *−32768* $\leq$ *a* $<$ *32768*.

- *DOWN3* 159 *a[3]*.<br>
  Same as *DOWN1*, except that *a* is a three-byte quantity in the range $-2^{23} \leq a < 2^{23}$.

- *DOWN4* 160 *a[4]*.<br>
  Same as *DOWN1*, except that *a* is a four-byte quantity in the range $-2^{31} \leq a < 2^{31}$.

- *Y0* 161.<br>
  Set *v &larr; v + y*; i.e., move down *y* units.
  With luck, this parameterless command will usually suffice, because the same kind of motion
  will occur several times in succession; the following commands explain how *y* gets particular values.

- *Y1* 162 *a[1]*.<br>
  Set *y &larr; a* and *v &larr; v + a*.
  The value of *a* is a signed quantity in two's complement notation, *−128* $\leq$ *a* $<$ *128*.
  This command changes the current *y*&nbsp;spacing and moves down by *a*.

- *Y2* 163 *a[2]*.<br>
  Same as *Y1*, but *a* is two bytes long, *−32768* $\leq$ *a* $<$ *32768*.

- *Y3* 164 *a[3]*.<br>
  Same as *Y1*, but *a* is three bytes long, $-2^{23} \leq a < 2^{23}$.

- *Y4* 165 *a[4]*.<br>
  Same as *Y1*, but *a* is four bytes long, $-2^{31} \leq a < 2^{31}$.

- *Z0* 166.<br>
  Set *v &larr; v + z*; i.e., move down *z* units.
  The *'Z'* commands are like the *'Z'* commands except that they involve *z* instead of *y*.

- *Z1* 167 *a[1]*.<br>
  Set *z &larr; a* and *v &larr; v + a*.
  The value of *a* is a signed quantity in two's complement notation, *−128* $\leq$ *a* $<$ *128*.
  This command changes the current *z*&nbsp;spacing and moves down by *a*.

- *Z2* 168 *a[2]*.<br>
  Same as *Z1*, but *a* is two bytes long, *−32768* $\leq$ *a* $<$ *32768*.

- *Z3* 169 *a[3]*.<br>
  Same as *Z1*, but *a* is three bytes long, $-2^{23} \leq a < 2^{23}$.

- *Z4* 170 *a[4]*.<br>
  Same as *Z1*, but *a* is four bytes long, $-2^{31} \leq a < 2^{31}$.

- *FNT_NUM_0* 171.<br>
  Set *f &larr; 0*.
  Font 0 must previously have been defined by a *FNT_DEF* instruction, as explained below.

- *FNT_NUM_1* through *FNT_NUM_63* (opcodes 172 to 234).<br>
  Set *f &larr; 1*, $\dots$, *f &larr; 63*, respectively.

- *FNT1* 235 *k[1]*.<br>
  Set *f &larr; k*.
  $\TeX82$ uses this command for font numbers in the range *64* $\leq$ *k* $<$ *256*.

- *FNT2* 236 *k[2]*.<br>
  Same as *FNT1*, except that *k*&nbsp;is two bytes long, so it is in the range *0* $\leq$ *k* $<$ *65536*.
  $\TeX82$ never generates this command, but large font numbers may prove useful
  for specifications of color or texture, or they may be used for special fonts
  that have fixed numbers in some external coding scheme.

- *FNT3* 237 *k[3]*.<br>
  Same as *FNT1*, except that *k*&nbsp;is three bytes long, so it can be as large as $2^{24} - 1$.

- *FNT4* 238 *k[4]*.<br>
  Same as *FNT1*, except that *k*&nbsp;is four bytes long; this is for the really big font numbers (and for the negative ones).

- *XXX1* 239 *k[1]* *x[k]*.<br>
  This command is undefined in general; it functions as a *(k + 2)*-byte *NOP* unless special `DVI`-reading programs are being used.
  $\TeX82$ generates *XXX1* when a short enough `\special` appears, setting *k* to the number of bytes being sent.
  It is recommended that *x* be a string having the form of a keyword followed by possible parameters relevant to that keyword.

- *XXX2* 240 *k[2]* *x[k]*.<br>
  Like *XXX1*, but *0* $\leq$ *k* $<$ *65536*.

- *XXX3* 241 *k[3]* *x[k]*.<br>
  Like *XXX1*, but *0* $\leq$ *k* $<$ $2^{24}$.

- *XXX4* 242 *k[4]* *x[k]*.<br>
  Like *XXX1*, but *k* can be ridiculously large.
  $\TeX82$ uses *XXX4* when sending a string of length 256 or more.

- *FNT_DEF1* 243 *k[1]* *c[4]* *s[4]* *d[4]* *a[1]* *l[1]* *n[a + l]*.<br>
  Define font *k*, where *0* $\leq$ *k* $<$ *256*; font definitions will be explained shortly.

- *FNT_DEF2* 244 *k[2]* *c[4]* *s[4]* *d[4]* *a[1]* *l[1]* *n[a + l]*.<br>
  Define font *k*, where *0* $\leq$ *k* $<$ *65536*.

- *FNT_DEF3* 245 *k[3]* *c[4]* *s[4]* *d[4]* *a[1]* *l[1]* *n[a + l]*.<br>
  Define font *k*, where $0 \leq k < 2^{24}$.

- *FNT_DEF4* 246 *k[4]* *c[4]* *s[4]* *d[4]* *a[1]* *l[1]* *n[a + l]*.<br>
  Define font *k*, where $-2^{31} \leq k < 2^{31}$.

- *PRE* 247 *i[1]* *num[4]* *den[4]* *mag[4]* *k[1]* *x[k]*.<br>
  Beginning of the preamble; this must come at the very beginning of the file.
  Parameters *i*, *num*, *den*, *mag*, *k*, and *x* are explained below.

- *POST* 248.<br>
  Beginning of the postamble, see below.

- *POST_POST* 249.<br>
  Ending of the postamble, see below.

Commands 250--255 are undefined at the present time.
