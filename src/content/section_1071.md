# Section 1071

Now let's turn to the question of how `\hbox` is treated.
We actually need to consider also a slightly larger context, since constructions like '`\setbox3=\hbox...`' and '`\leaders\hbox...`' and '`\lower3.8pt\hbox...`' are supposed to invoke quite different actions after the box has been packaged.
Conversely, constructions like '`\setbox3=`' can be followed by a variety of different kinds of boxes, and we would like to encode such things in an efficient way.

In other words, there are two problems: to represent the context of a box, and to represent its type.

The first problem is solved by putting a "context code" on the *save_stack*, just below the two entries that give the dimensions produced by *scan_spec*.
The context code is either a (signed) shift amount, or it is a large integer $\geq$ *BOX_FLAG*, where *BOX_FLAG* = $2^{30}$.
Codes *BOX_FLAG* through *BOX_FLAG + 255* represent '`\setbox0`' through '`\setbox255`';
codes *BOX_FLAG + 256* through *BOX_FLAG + 511* represent '`\global\setbox0`' through '`\global\setbox255`';
code *BOX_FLAG + 512* represents '`\shipout`';
and codes *BOX_FLAG + 513* through *BOX_FLAG + 515* represent '`\leaders`', '`\cleaders`', and '`\xleaders`'.

The second problem is solved by giving the command code *MAKE_BOX* to all control sequences that produce a box, and by using the following *chr_code* values to distinguish between them: *BOX_CODE*, *COPY_CODE*, *LAST_BOX_CODE*, *VSPLIT_CODE*, *VTOP_CODE*, *VTOP_CODE + VMODE*, and *VTOP_CODE + HMODE*, where the latter two are used to denote `\vbox` and `\hbox`, respectively.

```c include/constants.h
#define BOX_FLAG      0x40000000       // context code for '\setbox0'
#define SHIP_OUT_FLAG (BOX_FLAG + 512) // context code for '\shipout'
#define LEADER_FLAG   (BOX_FLAG + 513) // context code for '\leaders'
#define BOX_CODE      0                // |chr_code| for '\box'
#define COPY_CODE     1                // |chr_code| for '\copy'
#define LAST_BOX_CODE 2                // |chr_code| for '\lastbox'
#define VSPLIT_CODE   3                // |chr_code| for '\vsplit'
#define VTOP_CODE     4                // |chr_code| for '\vtop'
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("moveleft", HMOVE, 1);
primitive("moveright", HMOVE, 0);
primitive("raise", VMOVE, 1);
primitive("lower", VMOVE, 0);

primitive("box", MAKE_BOX, BOX_CODE);
primitive("copy", MAKE_BOX, COPY_CODE);
primitive("lastbox", MAKE_BOX, LAST_BOX_CODE);
primitive("vsplit", MAKE_BOX, VSPLIT_CODE);
primitive("vtop", MAKE_BOX, VTOP_CODE);
primitive("vbox", MAKE_BOX, VTOP_CODE + VMODE);
primitive("hbox", MAKE_BOX, VTOP_CODE + HMODE);
primitive("shipout", LEADER_SHIP, A_LEADERS - 1); // |SHIP_OUT_FLAG = LEADER_FLAG - 1|
primitive("leaders", LEADER_SHIP, A_LEADERS);
primitive("cleaders", LEADER_SHIP, C_LEADERS);
primitive("xleaders", LEADER_SHIP, X_LEADERS);
```
