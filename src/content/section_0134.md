# Section 134

A *CHAR_NODE*, which represents a single character, is the most important kind of node because it accounts for the vast majority of all boxes.
Special precautions are therefore taken to ensure that a *CHAR_NODE* does not take up much memory space.
Every such node is one word long, and in fact it is identifiable by this property, since other kinds of nodes have at least two words, and they appear in *mem* locations less than *hi_mem_min*.
This makes it possible to omit the *type* field in a *CHAR_NODE*, leaving us room for two bytes that identify a *font* and a *character* within that font.

Note that the format of a *CHAR_NODE* allows for up to 256 different fonts and up to 256 characters per font; but most implementations will probably limit the total number of fonts to fewer than 75 per job, and most fonts will stick to characters whose codes are less than 128 (since higher codes are more difficult to access on most keyboards).

Extensions of $\TeX$ intended for oriental languages will need even more than 256$\times$256 possible characters, when we consider different sizes and styles of type.
It is suggested that Chinese and Japanese fonts be handled by representing such characters in two consecutive *CHAR_NODE* entries:
The first of these has *font = FONT_BASE*, and its *link* points to the second;
the second identifies the font and the character dimensions.
The saving feature about oriental characters is that most of them have the same box dimensions. The *character* field of the first *CHAR_NODE* is a *"charext"* that distinguishes between graphic symbols whose dimensions are identical for typesetting purposes. (See the `METAFONT` manual.)
Such an extension of $\TeX$ would not be difficult; further details are left to the reader.

In order to make sure that the *character* code fits in a quarterword, $\TeX$ adds the quantity *MIN_QUARTERWORD* to the actual code.

Character nodes appear only in horizontal lists, never in vertical lists.

```c include/datastructures.h
#define is_char_node(X) ((X) >= hi_mem_min) // does the argument point to a |CHAR_NODE|?
#define font            type                // the font code in a |CHAR_NODE|
#define character       subtype             // the character code in a |CHAR_NODE|
```
