# Section 11

The following parameters can be changed at compile time to extend or reduce $\TeX$’s capacity.
They may have different values in `INITEX` and in production versions of $\TeX$.

> ![NOTE]
> Specific values for the `TRIP` test have been added in blocks `#ifdef TRIP`.

```c include/constants.h
#ifdef TRIP
#define MEM_MAX         3000
#define MEM_MIN         1
#else
#define MEM_MAX         30000 // greatest index in TeX's internal |mem| array; must be strictly less than |MAX_HALFWORD|; must be equal to |MEM_TOP| in INITEX, otherwise |>= MEM_TOP|
#define MEM_MIN         0     // smallest index in TeX's internal |mem| array; must be |MIN_HALFWORD| or more; must be equal to |MEM_BOT| in INITEX, otherwise |<= MEM_BOT|
#endif

#define BUF_SIZE        200000// maximum number of characters simultaneously present in current lines of open files and in control sequences between \csname and \endcsname; must not exceed |MAX_HALFWORD|

#ifdef TRIP
#define ERROR_LINE      64
#define HALF_ERROR_LINE 32
#define MAX_PRINT_LINE  72
#else
#define ERROR_LINE      72    // width of context lines on terminal error messages 
#define HALF_ERROR_LINE 42    // width of first lines of contexts in terminal error messages; should be between 30 and |ERROR_LINE - 15|
#define MAX_PRINT_LINE  79    // width of longest text lines output; should be at least 60
#endif

#define STACK_SIZE      200   // maximum number of simultaneous input sources
#define MAX_IN_OPEN     6     // maximum number of input files and error insertions that can be going on simultaneously
#define FONT_MAX        75    // maximum internal font number; must not exceed |MAX_QUARTERWORD| and must be at most |FONT_BASE + 256|
#define FONT_MEM_SIZE   20000 // number of words of |font_info| for all fonts
#define PARAM_SIZE      60    // maximum number of simultaneous macro parameters
#define NEST_SIZE       40    // maximum number of semantic levels simultaneously active
#define MAX_STRINGS     3000  // maximum number of strings; must not exceed |MAX_HALFWORD|
#define POOL_SIZE       32000 // maximum number of characters in strings, including all error messages and help texts, and the names of all fonts and control sequences;
#define SAVE_SIZE       600   // space for saving values outside of current group; must be at most |MAX_HALFWORD|
#define TRIE_SIZE       8000  // space for hyphenation patterns; should be larger for INITEX than it is in production versions of TeX
#define TRIE_OP_SIZE    500   // space for "opcodes" in the hyphenation patterns
#define DVI_BUF_SIZE    800   // size of the output buffer; must be a multiple of 8
#define FILE_NAME_SIZE  40    // file names shouldn't be longer than this
```
