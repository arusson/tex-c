# Section 146

A *WHATSIT_NODE* is a wild card reserved for extensions to $\TeX$.
The *subtype* field in its first word says what *'whatsit'* it is, and implicitly determines the node size (which must be 2 or more) and the format of the remaining words.
When a *WHATSIT_NODE* is encountered in a list, special actions are invoked; knowledgeable people who are careful not to mess up the rest of $\TeX$ are able to make $\TeX$ do new things by adding code at the end of the program.
For example, there might be a '$\TeX$nicolor' extension to specify different colors of ink, and the whatsit node might contain the desired parameters.

The present implementation of $\TeX$ treats the features associated with '`\write`' and '`\special`' as if they were extensions, in order to illustrate how such routines might be coded.
We shall defer further discussion of extensions until the end of this program.

```c include/constants.h
#define WHATSIT_NODE 8 // |type| of special extension nodes
```
