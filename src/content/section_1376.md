# Section 1376

The `\language` extension is somewhat different.
We need a subroutine that comes into play when a character of a non-*clang* language is being appended to the current paragraph.

```c << Declare action procedures for use by |main_control| >>+=
void fix_language() {
    ASCII_code l; // the new current language
    if (language <= 0) {
        l = 0;
    }
    else if (language > 255) {
        l = 0;
    }
    else {
        l = language;
    }
    if (l != clang) {
        new_whatsit(LANGUAGE_NODE, SMALL_NODE_SIZE);
        what_lang(tail) = l;
        clang = l;
        what_lhm(tail) = norm_min(left_hyphen_min);
        what_rhm(tail) = norm_min(right_hyphen_min);
    }
}
```
