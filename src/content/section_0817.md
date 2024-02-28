# Section 817

When looking for optimal line breaks, $\TeX$ creates a "break node" for each break that is *feasible*, in the sense that there is a way to end a line at the given place without requiring any line to stretch more than a given tolerance.
A break node is characterized by three things: the position of the break (which is a pointer to a *GLUE_NODE*, *MATH_NODE*, *PENALTY_NODE*, or *DISC_NODE*); the ordinal number of the line that will follow this breakpoint; and the fitness classification of the line that has just ended, i.e., *TIGHT_FIT*, *DECENT_FIT*, *LOOSE_FIT*, or *VERY_LOOSE_FIT*.

```c include/constants.h
#define TIGHT_FIT      3 // fitness classification for lines shrinking 0.5 to 1.0 of their shrinkability
#define LOOSE_FIT      1 // fitness classification for lines stretching 0.5 to 1.0 of their stretchability
#define VERY_LOOSE_FIT 0 // fitness classification for lines stretching more than their stretchability
#define DECENT_FIT     2 // fitness classification for all other lines
```
