# Section 781

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case TAB_MARK:
    if (chr_code == SPAN_CODE) {
        print_esc("span");
    }
    else {
        chr_cmd("alignment tab character ");
    }
    break;

case CAR_RET:
    if (chr_code == CR_CODE) {
        print_esc("cr");
    }
    else {
        print_esc("crcr");
    }
    break;
```
