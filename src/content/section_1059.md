# Section 1059

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case HSKIP:
    switch (chr_code) {
    case SKIP_CODE:
        print_esc("hskip");
        break;
    
    case FIL_CODE:
        print_esc("hfil");
        break;
  
    case FILL_CODE:
        print_esc("hfill");
        break;

    case SS_CODE:
        print_esc("hss");
        break;

    default:
        print_esc("hfilneg");
    }
    break;

case VSKIP:
    switch (chr_code) {
    case SKIP_CODE:
        print_esc("vskip");
        break;
    
    case FIL_CODE:
        print_esc("vfil");
        break;
    
    case FILL_CODE:
        print_esc("vfill");
        break;
    
    case SS_CODE:
        print_esc("vss");
        break;
    
    default:
        print_esc("vfilneg");
    }
    break;

case MSKIP:
    print_esc("mskip");
    break;

case KERN:
    print_esc("kern");
    break;

case MKERN:
    print_esc("mkern");
    break;
```
