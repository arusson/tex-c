# Section 375

An *END_TEMPLATE* command is effectively changed to an *ENDV* command by the following code.
(The reason for this is discussed below; the *FROZEN_END_TEMPLATE* at the end of the template has passed the *check_outer_validity* test, so its mission of error detection has been accomplished.)

```c << Insert a token containing |FROZEN_ENDV| >>=
cur_tok = CS_TOKEN_FLAG + FROZEN_ENDV;
back_input();
```
