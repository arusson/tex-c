# Section 390

Before we put a new token list on the input stack, it is wise to clean off all token lists that have recently been depleted.
Then a user macro that ends with a call to itself will not require unbounded stack space.

```c << Feed the macro body and its parameters to the scanner >>=
while (state == TOKEN_LIST
    && loc == null
    && token_type != V_TEMPLATE)
{
    end_token_list(); // conserve stack space
}
begin_token_list(ref_count, MACRO);
name = warning_index;
loc = link(r);
if (n > 0) {
    if (param_ptr + n > max_param_stack) {
        max_param_stack = param_ptr + n;
        if (max_param_stack > PARAM_SIZE) {
            overflow("parameter stack size", PARAM_SIZE);
        }
    }
    for(m = 0; m < n; m++) {
        param_stack[param_ptr + m] = pstack[m];
    }
    param_ptr += n;
}
```
