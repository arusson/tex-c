# Section 1032

The following part of the program was first written in a structured manner, according to the philosophy that "premature optimization is the root of all evil".
Then it was rearranged into pieces of spaghetti so that the most common actions could proceed with little or no redundancy.

The original unoptimized form of this algorithm resembles the *reconstitute* procedure, which was described earlier in connection with hyphenation.
Again we have an implied "cursor" between characters *cur_l* and *cur_r*.
The main difference is that the *lig_stack* can now contain a charnode as well as pseudo-ligatures; that stack is now usually nonempty, because the next character of input (if any) has been appended to it.
In *main_control* we have

$$
\v{cur\_r} = \begin{cases}
\v{character}(\v{lig\_stack}), & \textsf{if } \v{lig\_stack} > \v{null};\\
\v{font\_bchar}[\v{cur\_font}], & \textsf{otherwise};
\end{cases}
$$

except when *character(lig_stack) = font_false_bchar[cur_font]*.
Several additional global variables are needed.

```c << Global variables >>+=
internal_font_number main_f; // the current font
memory_word main_i;          // character information bytes for |cur_l|
memory_word main_j;          // ligature/kern command
int main_k;                  // index into |font_info|
pointer main_p;              // temporary register for list manipulation
int main_s;                  // space factor value
halfword bchar;              // boundary character of current font, or |NON_CHAR|
halfword false_bchar;        // nonexistent character matching |bchar|, or |NON_CHAR|
bool cancel_boundary;        // should the left boundary be ignored?
bool ins_disc;               // should we insert a discretionary node?
```
