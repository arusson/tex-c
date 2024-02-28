# Section 892

The letters $c_1\ldots c_n$ that are candidates for hyphenation are placed into an array called *hc*; the number *n* is placed into *hn*; pointers to nodes $p_{a - 1}$ and&nbsp;$p_b$ in the description above are placed into variables *ha* and *hb*; and the font number is placed into *hf*.

```c << Global variables >>+=
quarterword hc[66];                       // word to be hyphenated
small_number hn;                          // the number of positions occupied in |hc|; not always a |small_number|
pointer ha, hb;                           // nodes |ha .. hb| should be replaced by the hyphenated result
internal_font_number hf;                  // font number of the letters in |hc|
quarterword hu[64];                       // like |hc|, before conversion to lowercase
int hyf_char;                             // hyphen character of the relevant font
ASCII_code cur_lang, init_cur_lang;       // current hyphenation table of interest
int l_hyf, r_hyf, init_l_hyf, init_r_hyf; // limits on fragment sizes
halfword hyf_bchar;                       // boundary character after c_n
```
