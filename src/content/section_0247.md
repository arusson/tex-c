# Section 247

The final region of *eqtb* contains the dimension parameters defined here, and the 256 `\dimen` registers.

```c include/constants.h
#define PAR_INDENT_CODE           0           // indentation of paragraphs
#define MATH_SURROUND_CODE        1           // space around math in text
#define LINE_SKIP_LIMIT_CODE      2           // threshold for |line_skip| instead of |baseline_skip|
#define HSIZE_CODE                3           // line width in horizontal mode
#define VSIZE_CODE                4           // page height in vertical mode
#define MAX_DEPTH_CODE            5           // maximum depth of boxes on main pages
#define SPLIT_MAX_DEPTH_CODE      6           // maximum depth of boxes on split pages
#define BOX_MAX_DEPTH_CODE        7           // maximum depth of explicit vboxes
#define HFUZZ_CODE                8           // tolerance for overfull hbox messages
#define VFUZZ_CODE                9           // tolerance for overfull vbox messages
#define DELIMITER_SHORTFALL_CODE  10          // maximum amount uncovered by variable delimiters
#define NULL_DELIMITER_SPACE_CODE 11          // blank space in null delimiters
#define SCRIPT_SPACE_CODE         12          // extra space after subscript or superscript
#define PRE_DISPLAY_SIZE_CODE     13          // length of text preceding a display
#define DISPLAY_WIDTH_CODE        14          // length of line for displayed equation
#define DISPLAY_INDENT_CODE       15          // indentation of line for displayed equation
#define OVERFULL_RULE_CODE        16          // width of rule that identifies overfull hboxes
#define HANG_INDENT_CODE          17          // amount of hanging indentation
#define H_OFFSET_CODE             18          // amount of horizontal offset when shipping pages out
#define V_OFFSET_CODE             19          // amount of vertical offset when shipping pages out
#define EMERGENCY_STRETCH_CODE    20          // reduces badnesses on final pass of line-breaking
#define DIMEN_PARS                21          // total number of dimension parameters
#define SCALED_BASE (DIMEN_BASE + DIMEN_PARS) // table of 256 user-defined \dimen registers
#define EQTB_SIZE   (SCALED_BASE + 255)       // largest subscript of |eqtb|
```

```c include/datastructures.h
#define dimen(X)             eqtb[SCALED_BASE + (X)].sc
#define dimen_par(X)         eqtb[DIMEN_BASE + (X)].sc  // a scaled quantity
#define par_indent           dimen_par(PAR_INDENT_CODE)
#define math_surround        dimen_par(MATH_SURROUND_CODE)
#define line_skip_limit      dimen_par(LINE_SKIP_LIMIT_CODE)
#define hsize                dimen_par(HSIZE_CODE)
#define vsize                dimen_par(VSIZE_CODE)
#define max_depth            dimen_par(MAX_DEPTH_CODE)
#define split_max_depth      dimen_par(SPLIT_MAX_DEPTH_CODE)
#define box_max_depth        dimen_par(BOX_MAX_DEPTH_CODE)
#define hfuzz                dimen_par(HFUZZ_CODE)
#define vfuzz                dimen_par(VFUZZ_CODE)
#define delimiter_shortfall  dimen_par(DELIMITER_SHORTFALL_CODE)
#define null_delimiter_space dimen_par(NULL_DELIMITER_SPACE_CODE)
#define script_space         dimen_par(SCRIPT_SPACE_CODE)
#define pre_display_size     dimen_par(PRE_DISPLAY_SIZE_CODE)
#define display_width        dimen_par(DISPLAY_WIDTH_CODE)
#define display_indent       dimen_par(DISPLAY_INDENT_CODE)
#define overfull_rule        dimen_par(OVERFULL_RULE_CODE)
#define hang_indent          dimen_par(HANG_INDENT_CODE)
#define h_offset             dimen_par(H_OFFSET_CODE)
#define v_offset             dimen_par(V_OFFSET_CODE)
#define emergency_stretch    dimen_par(EMERGENCY_STRETCH_CODE)
```

```c io/other_printing.c
void print_length_param(int n) {
    switch(n) {
    case PAR_INDENT_CODE:
        print_esc("parindent");
        break;
    
    case MATH_SURROUND_CODE:
        print_esc("mathsurround");
        break;
    
    case LINE_SKIP_LIMIT_CODE:
        print_esc("lineskiplimit");
        break;
    
    case HSIZE_CODE:
        print_esc("hsize");
        break;
    
    case VSIZE_CODE:
        print_esc("vsize");
        break;
    
    case MAX_DEPTH_CODE:
        print_esc("maxdepth");
        break;
    
    case SPLIT_MAX_DEPTH_CODE:
        print_esc("splitmaxdepth");
        break;
    
    case BOX_MAX_DEPTH_CODE:
        print_esc("boxmaxdepth");
        break;
    
    case HFUZZ_CODE:
        print_esc("hfuzz");
        break;
    
    case VFUZZ_CODE:
        print_esc("vfuzz");
        break;
    
    case DELIMITER_SHORTFALL_CODE:
        print_esc("delimitershortfall");
        break;
    
    case NULL_DELIMITER_SPACE_CODE:
        print_esc("nulldelimiterspace");
        break;
    
    case SCRIPT_SPACE_CODE:
        print_esc("scriptspace");
        break;
    
    case PRE_DISPLAY_SIZE_CODE:
        print_esc("predisplaysize");
        break;
    
    case DISPLAY_WIDTH_CODE:
        print_esc("displaywidth");
        break;
    
    case DISPLAY_INDENT_CODE:
        print_esc("displayindent");
        break;
    
    case OVERFULL_RULE_CODE:
        print_esc("overfullrule");
        break;
    
    case HANG_INDENT_CODE:
        print_esc("hangindent");
        break;
    
    case H_OFFSET_CODE:
        print_esc("hoffset");
        break;
    
    case V_OFFSET_CODE:
        print_esc("voffset");
        break;
    
    case EMERGENCY_STRETCH_CODE:
        print_esc("emergencystretch");
        break;
    
    default:
        print("[unknown dimen parameter!]");
    }
}
```
