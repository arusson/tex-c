# Section 269

Here are the group codes that are used to discriminate between different kinds of groups.
They allow $\TeX$ to decide what special actions, if any, should be performed when a group ends.

Some groups are not supposed to be ended by right braces.
For example, the '`$`' that begins a math formula causes a *MATH_SHIFT_GROUP* to be started, and this should be terminated by a matching '`$`'.
Similarly, a group that starts with `\left` should end with `\right`, and one that starts with `\begingroup` should end with `\endgroup`.

```c include/constants.h
#define BOTTOM_LEVEL        0    // group code for the outside world
#define SIMPLE_GROUP        1    // group code for local structure only
#define HBOX_GROUP          2    // code for '\hbox{...}'
#define ADJUSTED_HBOX_GROUP 3    // code for '\hbox{...}' in vertical mode
#define VBOX_GROUP          4    // code for '\vbox{...}'
#define VTOP_GROUP          5    // code for '\vtop{...}'
#define ALIGN_GROUP         6    // code for '\halign{...}', '\valign{...}'
#define NO_ALIGN_GROUP      7    // code for '\noalign{...}'
#define OUTPUT_GROUP        8    // code for output routine
#define MATH_GROUP          9    // code for, e.g., `^{...}'
#define DISC_GROUP          10   // code for '\discretionary{...}{...}{...}'
#define INSERT_GROUP        11   // code for '\insert{...}', '\vadjust{...}'
#define VCENTER_GROUP       12   // code for '\vcenter{...}'
#define MATH_CHOICE_GROUP   13   // code for '\mathchoice{...}{...}{...}{...}'
#define SEMI_SIMPLE_GROUP   14   // code for '\begingroup...\endgroup'
#define MATH_SHIFT_GROUP    15   // code for '$...$'
#define MATH_LEFT_GROUP     16   // code for '\left...\right'
#define MAX_GROUP_CODE      16
```
