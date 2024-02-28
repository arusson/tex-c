# Section 543

Next comes the *char_info* array, which contains one *char_info_word* per character.
Each word in this part of the file contains six fields packed into four bytes as follows.

- first byte: *width_index* (8 bits)
- second byte: *height_index* (4 bits) times 16, plus *depth_index* (4&nbsp;bits)
- third byte: *italic_index* (6 bits) times 4, plus *tag* (2&nbsp;bits)
- fourth byte: *remainder* (8 bits)

The actual width of a character is *width[width_index]*, in design-size units;
this is a device for compressing information, since many characters have the same width.
Since it is quite common for many characters to have the same height, depth, or italic correction, the `TFM` format imposes a limit of 16 different heights, 16 different depths, and 64 different italic corrections.

The italic correction of a character has two different uses.
(a)&nbsp;In ordinary text, the italic correction is added to the width only if the $\TeX$ user specifies '`\/`' after the character.
(b)&nbsp;In math formulas, the italic correction is always added to the width, except with respect to the positioning of subscripts.

Incidentally, the relation *width[0] = height[0] = depth[0] = italic[0] = 0* should always hold, so that an index of zero implies a value of zero.
The *width_index* should never be zero unless the character does not exist in the font, since a character is valid if and only if it lies between *bc* and *ec* and has a nonzero *width_index*.
