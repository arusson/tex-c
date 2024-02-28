# Section 1027

```c << Recover from an unbalanced output routine >>=
print_err("Unbalanced output routine");
help2("Your sneaky output routine has problematic {'s and/or }'s.")
    ("I can't handle that very well; good luck.");
error();
do {
    get_token();
} while (loc != null);
// loops forever if reading from a file, since |null = MIN_HALFWORD <= 0|
```
