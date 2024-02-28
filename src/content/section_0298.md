# Section 298

The *print_cmd_chr* routine prints a symbolic interpretation of a command code and its modifier.
This is used in certain '`You can't`' error messages, and in the implementation of diagnostic routines like `\show`.

The body of *print_cmd_chr* is a rather tedious listing of print commands, and most of it is essentially an inverse to the *primitive* routine that enters a $\TeX$ primitive into *eqtb*.
Therefore much of this procedure appears elsewhere in the program, together with the corresponding *primitive* calls.

```c include/io.h
#define chr_cmd(X) print((X)); print_strnumber(chr_code)
```

```c io/display_tokens.c
void print_cmd_chr(quarterword cmd, halfword chr_code) {
    switch(cmd) {
    case LEFT_BRACE:
        chr_cmd("begin-group character ");
        break;
    
    case RIGHT_BRACE:
        chr_cmd("end-group character ");
        break;
    
    case MATH_SHIFT:
        chr_cmd("math shift character ");
        break;
    
    case MAC_PARAM:
        chr_cmd("macro parameter character ");
        break;
    
    case SUP_MARK:
        chr_cmd("superscript character ");
        break;
    
    case SUB_MARK:
        chr_cmd("subscript character ");
        break;
    
    case ENDV:
        print("end of alignment template");
        break;
    
    case SPACER:
        chr_cmd("blank space ");
        break;
    
    case LETTER:
        chr_cmd("the letter ");
        break;
    
    case OTHER_CHAR:
        chr_cmd("the character ");
        break;

    // << Cases of |print_cmd_chr| for symbolic printing of primitives >>

    default:
        print("[unknown command code!]");
    }
}
```
