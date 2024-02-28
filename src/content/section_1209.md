# Section 1209

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case PREFIX:
    if (chr_code == 1) {
        print_esc("long");
    }
    else if (chr_code == 2) {
        print_esc("outer");
    }
    else {
        print_esc("global");
    }
    break;

case DEF:
    if (chr_code == 0) {
        print_esc("def");
    }
    else if (chr_code == 1) {
        print_esc("gdef");
    }
    else if (chr_code == 2) {
        print_esc("edef");
    }
    else {
        print_esc("xdef");
    }
    break;
```
