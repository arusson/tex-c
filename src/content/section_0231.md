# Section 231

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case ASSIGN_TOKS:
    if (chr_code >= TOKS_BASE) {
        print_esc("toks");
        print_int(chr_code - TOKS_BASE);
    }
    else {
        switch(chr_code) {
        case OUTPUT_ROUTINE_LOC:
            print_esc("output");
            break;
        
        case EVERY_PAR_LOC:
            print_esc("everypar");
            break;
        
        case EVERY_MATH_LOC:
            print_esc("everymath");
            break;
        
        case EVERY_DISPLAY_LOC:
            print_esc("everydisplay");
            break;
        
        case EVERY_HBOX_LOC:
            print_esc("everyhbox");
            break;
        
        case EVERY_VBOX_LOC:
            print_esc("everyvbox");
            break;
        
        case EVERY_JOB_LOC:
            print_esc("everyjob");
            break;
        
        case EVERY_CR_LOC:
            print_esc("everycr");
            break;
        
        default:
            print_esc("errhelp");
        }
    }
    break;
```
