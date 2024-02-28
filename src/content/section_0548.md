# Section 548

So that is what `TFM` files hold.
Since $\TeX$ has to absorb such information about lots of fonts, it stores most of the data in a large array called *font_info*.
Each item of *font_info* is a *memory_word*; the *fix_word* data gets converted into *scaled* entries, while everything else goes into words of type *four_quarters*.

When the user defines `\font\f`, say, $\TeX$ assigns an internal number to the user's font&nbsp;`\f`.
Adding this number to *FONT_ID_BASE* gives the *eqtb* location of a "frozen" control sequence that will always select the font.

```c << Types in the outer block >>+=
typedef int internal_font_number; // |font| in a |CHAR_NODE|
typedef int font_index;           // index into |font_info|
```
