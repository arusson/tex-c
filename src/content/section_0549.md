# Section 549

Here now is the (rather formidable) array of font arrays.

```c include/constants.h
#define NON_CHAR    256 // a |halfword| code that can't match a real character
#define NON_ADDRESS 0   // a spurious |bchar_label|
```

```c << Global variables >>+=
memory_word font_info[FONT_MEM_SIZE + 1]; // the big collection of font data
font_index fmem_ptr;                      // first unused word of |font_info|
internal_font_number font_ptr;            // largest internal font number in use
memory_word font_check[FONT_MAX + 1];     // check sum
scaled font_size[FONT_MAX + 1];           // "at" size
scaled font_dsize[FONT_MAX + 1];          // "design" size
font_index font_params[FONT_MAX + 1];     // how many font parameters are present
str_number font_name[FONT_MAX + 1];       // name of the font
str_number font_area[FONT_MAX + 1];       // area of the font
eight_bits font_bc[FONT_MAX + 1];         // beginning (smallest) character code
eight_bits font_ec[FONT_MAX + 1];         // ending (largest) character code
pointer font_glue[FONT_MAX + 1];          // glue specification for interword space, |null| if not allocated
bool font_used[FONT_MAX + 1];             // has a character from this font actually appeared in the output?
int hyphen_char[FONT_MAX + 1];            // current \hyphenchar values
int skew_char[FONT_MAX + 1];              // current \skewchar values
font_index bchar_label[FONT_MAX + 1];     // start of |lig_kern| program for left boundary character, |NON_ADDRESS| if there is none
int font_bchar[FONT_MAX + 1];        // boundary character, |NON_CHAR| if there is none
int font_false_bchar[FONT_MAX + 1];  // |font_bchar| if it doesn't exist in the font, otherwise |NON_CHAR|
```
