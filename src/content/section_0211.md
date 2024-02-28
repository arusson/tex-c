# Section 211: The semantic nest

TeX is typically in the midst of building many lists at once.
For example, when a math formula is being processed, $\TeX$ is in math mode and working on an mlist;
this formula has temporarily interrupted $\TeX$ from being in horizontal mode and building the hlist of a paragraph;
and this paragraph has temporarily interrupted $\TeX$ from being in vertical mode and building the vlist for the next page of a document.
Similarly, when a `\vbox` occurs inside of an `\hbox`, $\TeX$ is temporarily interrupted from working in restricted horizontal mode, and it enters internal vertical mode.
The "semantic nest" is a stack that keeps track of what lists and modes are currently suspended.

At each level of processing we are in one of six modes:
- *VMODE* stands for vertical mode (the page builder);
- *HMODE* stands for horizontal mode (the paragraph builder);
- *MMODE* stands for displayed formula mode;
- *−VMODE* stands for internal vertical mode (e.g., in a `\vbox`);
- *−HMODE* stands for restricted horizontal mode (e.g., in an `\hbox`);
- *−MMODE* stands for math formula mode (not displayed).

The mode is temporarily set to zero while processing `\write` texts.

Numeric values are assigned to *VMODE*, *HMODE*, and *MMODE* so that $\TeX$'s "big semantic switch" can select the appropriate thing to do by computing the value *abs(mode) + cur_cmd*, where *mode* is the current mode and *cur_cmd* is the current command code.

```c include/constants.h
#define VMODE 1                         // vertical mode
#define HMODE (VMODE + MAX_COMMAND + 1) // horizontal mode
#define MMODE (HMODE + MAX_COMMAND + 1) // math mode
```

```c io/other_printing.c
// << Start file |other_printing.c| >>

// prints the mode represented by |m|
void print_mode(int m) {
    if (m > 0) {
        switch(m / (MAX_COMMAND + 1)) {
        case 0:
            print("vertical");
            break;
        
        case 1:
            print("horizontal");
            break;
        
        case 2:
            print("display math");
        }
    }
    else if (m == 0) {
        print("no");
    }
    else {
        switch ((-m) / (MAX_COMMAND + 1)) {
        case 0:
            print("internal vertical");
            break;
        
        case 1:
            print("restricted horizontal");
            break;
        
        case 2:
            print("math");
        }
    }
    print(" mode");
}
```
