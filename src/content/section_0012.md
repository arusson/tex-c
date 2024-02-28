# Section 12

Like the preceding parameters, the following quantities can be changed at compile time to extend or reduce $\TeX$'s capacity.
But if they are changed, it is necessary to rerun the initialization program `INITEX` to generate new tables for the production $\TeX$ program.
One can't simply make helter-skelter changes to the following constants, since certain rather complex initialization numbers are computed from them.
They are defined here using `WEB` macros, instead of being put into Pascal's **const** list, in order to emphasize this distinction.

```c include/constants.h
#ifdef TRIP
#define MEM_BOT    1
#define MEM_TOP    3000
#else
#define MEM_BOT    0     // smallest index in the |mem| array dumped by INITEX must not be less than |MEM_MIN|
#define MEM_TOP    30000 // largest index in the |mem| array dumped by INITEX; must be substantially larger than |MEM_BOT| and not greater than |MEM_MAX|
#endif

#define FONT_BASE  0     // smallest internal font number; must not be less than |MIN_QUARTERWORD|
#define HASH_SIZE  2100  // maximum number of control sequences; it should be at most about |(MEM_MAX - MEM_MIN)/10|
#define HASH_PRIME 1777  // a prime number equal to about 85% of |HASH_SIZE|
#define HYPH_SIZE  307   // another prime; the number of \hyphenation exceptions
```
