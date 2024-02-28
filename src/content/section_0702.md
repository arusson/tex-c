# Section 702

We also need to compute the change in style between mlists and their subsidiaries.
The following macros define the subsidiary style for an overlined nucleus (*cramped_style*), for a subscript or a superscript (*sub_style* or *sup_style*), or for a numerator or denominator (*num_style* or *denom_style*).

```c include/texmath.h
#define cramped_style(X) (2*((X) / 2) + CRAMPED)                   // cramp the style
#define sub_style(X)     (2*((X) / 4) + SCRIPT_STYLE + CRAMPED)    // smaller and cramped
#define sup_style(X)     (2*((X) / 4) + SCRIPT_STYLE + ((X) % 2))  // smaller
#define num_style(X)     ((X) + 2 - 2*((X) / 6))                   // smaller unless already script-script
#define denom_style(X)   (2*((X) / 2) + CRAMPED + 2 - 2*((X) / 6)) // smaller, cramped
```
