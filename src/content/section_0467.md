# Section 467

Here's part of the *expand* subroutine that we are now ready to complete:

```c parser/build_tokens.c
void ins_the_toks() {
    link(GARBAGE) = the_toks();
    ins_list(link(TEMP_HEAD));
}
```
