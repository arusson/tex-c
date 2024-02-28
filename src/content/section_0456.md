# Section 456

```c << Scan for mu units and |goto attach_fraction| >>=
if (scan_keyword("mu")) {
    goto attach_fraction;
}
else {
    print_err("Illegal unit of measure (");
    print("mu inserted)");
    help4("The unit of measurement in math glue must be mu.")
        ("To recover gracefully from this error, it's best to")
        ("delete the erroneous units; e.g., type `2' to delete")
        ("two letters. (See Chapter 27 of The TeXbook.)");
    error();
    goto attach_fraction;
}
```
