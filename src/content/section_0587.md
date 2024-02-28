# Section 587

The preamble contains basic information about the file as a whole.
As stated above, there are six parameters:

<div align="center">

*i[1] num[4] den[4] mag[4] k[1] x[k]*.
</div>

The *i* byte identifies `DVI` format; currently this byte is always set to&nbsp;2.
(The value *i = 3* is currently used for an extended format that allows a mixture of right-to-left and left-to-right typesetting.
Some day we will set *i = 4*, when `DVI` format makes another incompatible change---perhaps in the year 2048.)

The next two parameters, *num* and *den*, are positive integers that define the units of measurement;
they are the numerator and denominator of a fraction by which all dimensions in the `DVI` file could be multiplied in order to get lengths in units of $10^{-7}$ meters.
Since 7227&nbsp;pt = 254&nbsp;cm, and since $\TeX$ works with scaled points where there are $2^{16}$&nbsp;sp in a point, $\TeX$ sets *num*$/$*den* = $(254\cdot10^5)/(7227\cdot2^{16}) = 25\,400\,000/473\,628\,672$.

The *mag* parameter is what $\TeX$ calls `\mag`, i.e., 1000 times the desired magnification.
The actual fraction by which dimensions are multiplied is therefore *mag*$\cdot$*num*$/$1000*den*.
Note that if a $\TeX$ source document does not call for any '`true`' dimensions, and if you change it only by specifying a different `\mag` setting, the `DVI` file that $\TeX$ creates will be completely unchanged except for the value of *mag* in the preamble and postamble.
(Fancy `DVI`-reading programs allow users to override the *mag*&nbsp;setting when a `DVI` file is being printed.)

Finally, *k* and *x* allow the `DVI` writer to include a comment, which is not interpreted further.
The length of comment *x* is *k*, where *0* $\leq$ *k* $<$ *256*.

```c include/constants.h
#define ID_BYTE 2 // identifies the kind of `DVI` files described here
```
