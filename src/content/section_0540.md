# Section 540

The first 24 bytes (6 words) of a `TFM` file contain twelve 16-bit integers that give the lengths of the various subsequent portions of the file.
These twelve integers are, in order:

<div align="center">
<div style="text-align: right; display: inline-block;">

*lf*<br>
*lh*<br>
*bc*<br>
*ec*<br>
*nw*<br>
*nh*<br>
*nd*<br>
*ni*<br>
*nl*<br>
*nk*<br>
*ne*<br>
*np*
</div>
<div style="text-align: left; display: inline-block;">
= length of the entire file, in words;<br>
= length of the header data, in words;<br>
= smallest character code in the font;<br>
= largest character code in the font;<br>
= number of words in the width table;<br>
= number of words in the height table;<br>
= number of words in the depth table;<br>
= number of words in the italic correction table;<br>
= number of words in the lig/kern table;<br>
= number of words in the kern table;<br>
= number of words in the extensible character table;<br>
= number of font parameter words.
</div>
</div>

They are all nonnegative and less than $2^{15}$.
We must have *bc − 1* $\leq$ *ec* $\leq$ *255*, and

<div align="center">

*lf = 6 + lh + (ec − bc + 1) + nw + nh + nd + ni + nl + nk + ne + np*.
</div>

Note that a font may contain as many as 256 characters (if *bc = 0* and *ec = 255*), and as few as 0 characters (if *bc = ec + 1*).

Incidentally, when two or more 8-bit bytes are combined to form an integer of 16 or more bits, the most significant bytes appear first in the file.
This is called BigEndian order.
