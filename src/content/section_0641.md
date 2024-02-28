# Section 641

Sometimes the user will generate a huge page because other error messages are being ignored.
Such pages are not output to the `dvi` file, since they may confuse the printing software.

```c << Update the values of |max_h| and |max_v|; but if the page is too large, |goto done| >>=
if (height(p) > MAX_DIMEN
    || depth(p) > MAX_DIMEN
    || height(p) + depth(p) + v_offset > MAX_DIMEN
    || width(p) + h_offset > MAX_DIMEN)
{
    print_err("Huge page cannot be shipped out");
    help2("The page just created is more than 18 feet tall or")
        ("more than 18 feet wide, so I suspect something went wrong.");
    error();
    if (tracing_output <= 0) {
        begin_diagnostic();
        print_nl("The following box has been deleted:");
        show_box(p);
        end_diagnostic(true);
    }
    goto done;
}
if (height(p) + depth(p) + v_offset > max_v) {
    max_v = height(p) + depth(p) + v_offset;
}
if (width(p) + h_offset > max_h) {
    max_h = width(p) + h_offset;
}
```
