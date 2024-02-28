# Section 1195

```c << Check that the necessary fonts for math symbols are present; if not, flush the current math lists and set |danger = true| >>=
if (font_params[fam_fnt(2 + TEXT_SIZE)] < TOTAL_MATHSY_PARAMS
    || font_params[fam_fnt(2 + SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS
    || font_params[fam_fnt(2 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS)
{
    print_err("Math formula deleted: Insufficient symbol fonts");
    help3("Sorry, but I can't typeset math unless \\textfont 2")
        ("and \\scriptfont 2 and \\scriptscriptfont 2 have all")
        ("the \\fontdimen values needed in math symbol fonts.");
    error();
    flush_math();
    danger = true;
}
else if (font_params[fam_fnt(3 + TEXT_SIZE)] < TOTAL_MATHEX_PARAMS
    || font_params[fam_fnt(3 + SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS
    || font_params[fam_fnt(3 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS)
{
    print_err("Math formula deleted: Insufficient extension fonts");
    help3("Sorry, but I can't typeset math unless \\textfont 3")
        ("and \\scriptfont 3 and \\scriptscriptfont 3 have all")
        ("the \\fontdimen values needed in math extension fonts.");
    error();
    flush_math();
    danger = true;
}
```
