# Section 225

Sometimes we need to convert $\TeX$'s internal code numbers into symbolic form.
The *print_skip_param* routine gives the symbolic name of a glue parameter.

```c io/other_printing.c
void print_skip_param(int n) {
    switch(n) {
    case LINE_SKIP_CODE:
        print_esc("lineskip");
        break;
    
    case BASELINE_SKIP_CODE:
        print_esc("baselineskip");
        break;
    
    case PAR_SKIP_CODE:
        print_esc("parskip");
        break;
    
    case ABOVE_DISPLAY_SKIP_CODE:
        print_esc("abovedisplayskip");
        break;
    
    case BELOW_DISPLAY_SKIP_CODE:
        print_esc("belowdisplayskip");
        break;
    
    case ABOVE_DISPLAY_SHORT_SKIP_CODE:
        print_esc("abovedisplayshortskip");
        break;
    
    case BELOW_DISPLAY_SHORT_SKIP_CODE:
        print_esc("belowdisplayshortskip");
        break;
    
    case LEFT_SKIP_CODE:
        print_esc("leftskip");
        break;
    
    case RIGHT_SKIP_CODE:
        print_esc("rightskip");
        break;
    
    case TOP_SKIP_CODE:
        print_esc("topskip");
        break;
    
    case SPLIT_TOP_SKIP_CODE:
        print_esc("splittopskip");
        break;
    
    case TAB_SKIP_CODE:
        print_esc("tabskip");
        break;
    
    case SPACE_SKIP_CODE:
        print_esc("spaceskip");
        break;
    
    case XSPACE_SKIP_CODE:
        print_esc("xspaceskip");
        break;
    
    case PAR_FILL_SKIP_CODE:
        print_esc("parfillskip");
        break;
    
    case THIN_MU_SKIP_CODE:
        print_esc("thinmuskip");
        break;
    
    case MED_MU_SKIP_CODE:
        print_esc("medmuskip");
        break;
    
    case THICK_MU_SKIP_CODE:
        print_esc("thickmuskip");
        break;
    
    default:
        print("[unknown glue parameter!]");
    }
}
```
