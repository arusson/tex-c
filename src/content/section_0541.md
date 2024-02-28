# Section 541

The rest of the `TFM` file may be regarded as a sequence of ten data
arrays having the informal specification

<div align="center">
<div style="text-align: right; display: inline-block;">

*header*: <br>
*char*:   <br>
*width*:  <br>
*height*: <br>
*depth*:  <br>
*italic*: <br>
*lig*:    <br>
*kern*:   <br>
*exten*:  <br>
*param*:
</div>
<div style="text-align: left; display: inline-block;">

**array** [0 .. *lh* − 1] **of** *stuff*<br>
**array** [*bc* .. *ec*]  **of** *char_info_word*<br>
**array** [0 .. *nw* − 1] **of** *fix_word*<br>
**array** [0 .. *nh* − 1] **of** *fix_word*<br>
**array** [0 .. *nd* − 1] **of** *fix_word*<br>
**array** [0 .. *ni* − 1] **of** *fix_word*<br>
**array** [0 .. *nl* − 1] **of** *lig_kern_command*<br>
**array** [0 .. *nk* − 1] **of** *fix_word*<br>
**array** [0 .. *ne* − 1] **of** *extensible_recipe*<br>
**array** [1 .. *np*]     **of** *fix_word*
</div>
</div>

The most important data type used here is a *fix_word*, which is a 32-bit representation of a binary fraction.
A *fix_word* is a signed quantity, with the two's complement of the entire word used to represent
negation.
Of the 32 bits in a *fix_word*, exactly 12 are to the left of the binary point;
thus, the largest *fix_word* value is $2048 - 2^{-20}$, and the smallest is $-2048$.
We will see below, however, that all but two of the *fix_word* values must lie between −16 and +16.
