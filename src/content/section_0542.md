# Section 542

The first data array is a block of header information, which contains general facts about the font.
The header must contain at least two words, *header[0]* and *header[1]*, whose meaning is explained below.
Additional header information of use to other software routines might also be included, but $\TeX82$ does not need to know about such details.
For example, 16 more words of header information are in use at the Xerox Palo Alto Research Center; the first ten specify the character coding scheme used (e.g., '`XEROX text`' or '`TeX math symbols`'), the next five give the font identifier (e.g., '`HELVETICA`' or '`CMSY`'), and the last gives the "face byte".
The program that converts `DVI` files to Xerox printing format gets this information by looking at the `TFM` file, which it needs to read anyway because of other information that is not explicitly repeated in `DVI`&nbsp;format.

- *header[0]* is a 32-bit check sum that $\TeX$ will copy into the `DVI` output file.
  Later on when the `DVI` file is printed, possibly on another computer,
  the actual font that gets used is supposed to have a check sum that agrees
  with the one in the `TFM` file used by $\TeX$.
  In this way, users will be warned about potential incompatibilities.
  (However, if the check sum is zero in either the font file or the `TFM`
  file, no check is made.)  The actual relation between this check sum and
  the rest of the `TFM` file is not important; the check sum is simply an
  identification number with the property that incompatible fonts almost
  always have distinct check sums.

- *header[1]* is a *fix_word* containing the design size of the font,
  in units of $\TeX$ points. This number must be at least 1.0; it is fairly arbitrary,
  but usually the design size is 10.0 for a "10 point" font, i.e., a font that was
  designed to look best at a 10-point size, whatever that really means.
  When a $\TeX$ user asks for a font '`at` $\delta$ `pt`', the effect is to override
  the design size and replace it by $\delta$, and to multiply the *x* and *y* coordinates
  of the points in the font image by a factor of $\delta$ divided by the design size.
  *All other dimensions in the `TFM` file are* fix_word *numbers in design-size units*,
  with the exception of *param[1]* (which denotes the slant ratio).
  Thus, for example, the value of *param[6]*, which defines the `em` unit, is often
  the *fix_word* value $2^{20} = 1.0$, since many fonts have a design size equal to one em.
  The other dimensions must be less than 16 design-size units in absolute value;
  thus, *header[1]* and *param[1]* are the only *fix_word* entries in the whole
  `TFM` file whose first byte might be something besides 0 or 255.
