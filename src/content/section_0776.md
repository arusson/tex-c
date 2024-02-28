# Section 776

When `\halign` is used as a displayed formula, there should be no other pieces of mlists present.

```c << Check for improper alignment in displayed math >>=
if (mode == MMODE
    && (tail != head || incompleat_noad != null))
{
    print_err("Improper ");
    print_esc("halign");
    print(" inside $$'s");
    help3("Displays can use special alignments (like \\eqalignno)")
        ("only if nothing but the alignment itself is between $$'s.")
        ("So I've deleted the formulas that preceded this alignment.");
    error();
    flush_math();
}
```
