# Section 994

$\TeX$ is not always in vertical mode at the time *build_page* is called; the current mode reflects what $\TeX$ should return to, after the contribution list has been emptied.
A call on *build_page* should be immediately followed by '**goto** *big_switch*', which is $\TeX$'s central control point.

```c builder/page_builder.c
// << Declare the procedure called |fire_up| >>

// append contributions to the current page
void build_page() {
    pointer p;          // the node being appended
    pointer q, r;       // nodes being examined
    int b, c;           // badness and cost of current page
    int pi = 0;         // penalty to be added to the badness
    int n;              // insertion box number
    scaled delta, h, w; // sizes used for insertion calculations
    
    if (link(CONTRIB_HEAD) == null || output_active) {
        return;
    }
    do {
continue_lbl:
        p = link(CONTRIB_HEAD);
        
        // << Update the values of |last_glue|, |last_penalty|, and |last_kern| >>
        
        // << Move node |p| to the current page; if it is time for a page break, put the nodes following the break back onto the contribution list, and |return| to the user's output routine if there is one >>
    } while (link(CONTRIB_HEAD) != null);
    
    // << Make the contribution list empty by setting its tail to |CONTRIB_HEAD| >>
}
```
