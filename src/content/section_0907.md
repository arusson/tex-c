# Section 907

The reconstitution procedure shares many of the global data structures by which $\TeX$ has processed the words before they were hyphenated.
There is an implied "cursor" between characters *cur_l* and *cur_r*;
these characters will be tested for possible ligature activity.
If *ligature_present* then *cur_l* is a ligature character formed from the original characters following *cur_q* in the current translation list.
There is a "ligature stack" between the cursor and character *j + 1*, consisting of pseudo-ligature nodes linked together by their *link* fields.
This stack is normally empty unless a ligature command has created a new character that will need to be processed later.
A pseudo-ligature is a special node having a *character* field that represents a potential ligature and a *lig_ptr* field that points to a *CHAR_NODE* or is *null*.
We have

$$
\v{cur\_r} = \begin{cases}
    \v{character}(\v{lig\_stack}), & \textsf{if } \v{lig\_stack} > \v{null}; \\
    \v{qi}(\v{hu}[j + 1]),         & \textsf{if } \v{lig\_stack} = \v{null} \textsf{ and } j < n; \\
    \v{bchar},                          & \textsf{if } \v{lig\_stack} = \v{null} \textsf{ and } j = n.
\end{cases}
$$

```c << Global variables >>+=
halfword cur_l, cur_r; // characters before and after the cursor
pointer cur_q;         // where a ligature should be detached
pointer lig_stack;     // unfinished business to the right of the cursor
bool ligature_present; // should a ligature node be made for |cur_l|?
bool lft_hit, rt_hit;  // did we hit a ligature with a boundary character?
```
