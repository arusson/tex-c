# Section 1382

Here we add the files that needs to be included in each C file.
Having all them here makes it easier to add or remove things.

```c << Start file |alignment.c| >>=
#include <math.h>
#include "alignment.h"
#include "texerror.h"
#include "builder.h"
#include "texmath.h"
#include "parser.h"
#include "arithmetic.h"
```

```c << Start file |arithmetic.c| >>=
#include "tex.h"
```

```c << Start file |dvi.c| >>=
#include <math.h>
#include "dvi.h"
#include "texerror.h"
#include "extensions.h"
#include "font_metric.h"
```

```c << Start file |error.c| >>=
#include <stdlib.h>
#include "texerror.h"
#include "datastructures.h"
#include "parser.h"
```

```c << Start file |extensions.c| >>=
#include "extensions.h"
#include "parser.h"
#include "dvi.h"
#include "builder.h"
#include "texerror.h"
```

```c << Start file |font_metric.c| >>=
#include "font_metric.h"
#include "arithmetic.h"
#include "parser.h"
```

```c << Start file |global.c| >>=
#include "tex.h"
```

```c << Start file |init_cleanup.c| >>=
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "builder.h"
#include "conditional.h"
#include "dvi.h"
#include "texerror.h"
#include "parser.h"
#ifdef INIT
#include "breaker.h"
#endif
```

```c << Start file |strings.c| >>=
#include <string.h>
#include "strings.h"
#include "texerror.h"
```

```c << Start file |hyphenation.c| >>=
#include "breaker.h"
#include "font_metric.h"
```

```c << Start file |line_break.c| >>=
#include "breaker.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "arithmetic.h"
#include "extensions.h"
```

```c << Start file |page_break.c| >>=
#include "breaker.h"
#include "builder.h"
#include "texerror.h"
#include "parser.h"
#include "arithmetic.h"
```

```c << Start file |boxes_and_lists.c| >>=
#include <math.h>
#include "texerror.h"
#include "builder.h"
#include "parser.h"
#include "texmath.h"
#include "font_metric.h"
#include "alignment.h"
#include "dvi.h"
#include "breaker.h"
```

```c << Start file |chief.c| >>=
#include "builder.h"
#include "texerror.h"
#include "extensions.h"
#include "parser.h"
#include "font_metric.h"
#include "arithmetic.h"
#include "alignment.h"
#include "texmath.h"
```

```c << Start file |independent.c| >>=
#include "builder.h"
#include "texerror.h"
#include "parser.h"
#include "arithmetic.h"
#include "font_metric.h"
```

```c << Start file |packaging.c| >>=
#include "builder.h"
#include "font_metric.h"
#include "arithmetic.h"
```

```c << Start file |page_builder.c| >>=
#include "builder.h"
#include "breaker.h"
#include "texerror.h"
#include "parser.h"
#include "dvi.h"
#include "arithmetic.h"
```

```c << Start file |hash.c| >>=
#ifdef INIT
#include <string.h>
#endif
#include "datastructures.h"
#include "texerror.h"
#include "strings.h"
```

```c << Start file |memory.c| >>=
#include "datastructures.h"
#include "texerror.h"
#include "extensions.h"
#include "texmath.h"
```

```c << Start file |modes.c| >>=
#include "datastructures.h"
#include "texerror.h"
```

```c << Start file |nodes.c| >>=
#include "datastructures.h"
#include "arithmetic.h"
```

```c << Start file |stack.c| >>=
#include "datastructures.h"
#include "texerror.h"
```

```c << Start file |basic_printing.c| >>=
#include <math.h>
#include <string.h>
#include "datastructures.h"
#include "io.h"
```

```c << Start file |display_boxes.c| >>=
#include <math.h>
#include <string.h>
#include "datastructures.h"
#include "io.h"
#include "extensions.h"
#include "texmath.h"
```

```c << Start file |display_context.c| >>=
#include "datastructures.h"
#include "io.h"
```

```c << Start file |display_math.c| >>=
#include "io.h"
#include "texmath.h"
```

```c << Start file |display_tokens.c| >>=
#include "datastructures.h"
#include "io.h"
```

```c << Start file |dumping.c| >>=
#ifdef INIT
#include "texerror.h"
#include "breaker.h"
#else
#include "io.h"
#endif
#include "parser.h"
```

```c << Start file |files.c| >>=
#include <stdlib.h>
#include "datastructures.h"
#include "texerror.h"
#include "parser.h"
```

```c << Start file |other_printing.c| >>=
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "extensions.h"
#include "parser.h"
```

```c << Start file |terminal.c| >>=
#include <string.h>
#include "texerror.h"
#include "io.h"
#include "parser.h"
```

```c << Start file |math_lists.c| >>=
#include "arithmetic.h"
#include "breaker.h"
#include "builder.h"
#include "font_metric.h"
#include "parser.h"
#include "texmath.h"
```

```c << Start file |math_structures.c| >>=
#include "texmath.h"
```

```c << Start file |math_subroutines.c| >>=
#include "arithmetic.h"
#include "builder.h"
#include "font_metric.h"
#include "texmath.h"
```

```c << Start file |math_typesetting.c| >>=
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "texmath.h"
```

```c << Start file |build_tokens.c| >>=
#include "datastructures.h"
#include "texerror.h"
#include "parser.h"
```

```c << Start file |conditional.c| >>=
#include "conditional.h"
#include "parser.h"
#include "texerror.h"
```

```c << Start file |expand_next_token.c| >>=
#include "conditional.h"
#include "texerror.h"
#include "parser.h"
```

```c << Start file |filenames.c| >>=
#include "texerror.h"
#include "parser.h"
#include "strings.h"
```

```c << Start file |get_next_token.c| >>=
#include "alignment.h"
#include "texerror.h"
#include "parser.h"
```

```c << Start file |hyph_scan.c| >>=
#ifdef INIT
#include "breaker.h"
#endif
#include "texerror.h"
#include "parser.h"
```

```c << Start file |subroutines.c| >>=
#include <string.h>
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "parser.h"
```

```c << Start file |main.c| >>=
#include <stdlib.h>
#include <string.h>
#include "builder.h"
#include "io.h"
#include "parser.h"
```