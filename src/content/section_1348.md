# Section 1348

```c extensions.c
// << Start file |extensions.c| >>

// << Declare procedures needed in |do_extension| >>

void do_extension() {
    int k; // all-purpose integer
    pointer p; // all-purpose pointer
    switch (cur_chr) {
    case OPEN_NODE:
        // << Implement \openout >>
        break;
    
    case WRITE_NODE:
        // << Implement \write >>
        break;
    
    case CLOSE_NODE:
        // << Implement \closeout >>
        break;
    
    case SPECIAL_NODE:
        // << Implement \special >>
        break;
    
    case IMMEDIATE_CODE:
        // << Implement \immediate >>
        break;
    
    case SET_LANGUAGE_CODE:
        // << Implement \setlanguage >>
        break;
    
    default:
        confusion("ext1");
    }
}
```
