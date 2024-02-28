# Section 790

The token list *OMIT_TEMPLATE* just referred to is a constant token list that contains the special control sequence `\endtemplate` only.

```c << Initialize the special list heads and constant nodes >>=
info(OMIT_TEMPLATE) = END_TEMPLATE_TOKEN; // |link(OMIT_TEMPLATE) = null|
```
