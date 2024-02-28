# Section 493

When we skip conditional text, we keep track of the line number where skipping began, for use in error messages.

```c << Global variables >>+=
int skip_line; // skipping began here
```
