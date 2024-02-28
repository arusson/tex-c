# Section 331

To get $\TeX$'s whole input mechanism going, we perform the following actions.

```c << Initialize the input routines >>=
input_ptr = 0;
max_in_stack = 0;
in_open = 0;
open_parens = 0;
max_buf_stack = 0;
param_ptr = 0;
max_param_stack = 0;
memset(buffer, 0, BUF_SIZE + 1);
scanner_status = NORMAL;
warning_index = null;
first = 1;
state = NEW_LINE;
start = 1;
index = 0;
line = 0;
name = 0;
force_eof = false;
align_state = 1000000;
if (!init_terminal(argc, argv)) {
    exit(0);
}
limit = last;
first = last + 1; // |init_terminal| has set |loc| and |last|
```
