# Section 520

A messier routine is also needed, since format file names must be scanned before $\TeX$'s string mechanism has been initialized.
We shall use the global variable *tex_format_default* to supply the text for default system areas
and extensions related to format files.

> ![NOTE]
> String `".fmt"` must be added in the pool.

```c include/constants.h
#define FORMAT_DEFAULT_LENGTH 20      // length of the |tex_format_default| string
#define FORMAT_AREA_LENGTH    11      // length of its area part
#define FORMAT_EXT_LENGTH     4       // length of its '.fmt' part
#define FORMAT_EXTENSION      FMT_EXT // the extension, as a WEB constant
```

```c << Global variables >>+=
char tex_format_default[FORMAT_DEFAULT_LENGTH];
```

```c << Read the other strings >>+=
put_string(".fmt"); // FMT_EXT: 260
```

```c << Internal strings numbers in the pool >>+=
#define FMT_EXT 260
```
