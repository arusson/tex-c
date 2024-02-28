# Section 459

```c << Complain about unknown unit and |goto done2| >>=
print_err("Illegal unit of measure (");
print("pt inserted)");
help6("Dimensions can be in units of em, ex, in, pt, pc,")
    ("cm, mm, dd, cc, bp, or sp; but yours is a new one!")
    ("I'll assume that you meant to say pt, for printer's points.")
    ("To recover gracefully from this error, it's best to")
    ("delete the erroneous units; e.g., type `2' to delete")
    ("two letters. (See Chapter 27 of The TeXbook.)");
error();
goto done2;
```
