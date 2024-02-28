# Section 997

The code here is an example of a many-way switch into routines that merge together in different places.
Some people call this unstructured programming, but the author doesn't see much wrong with it, as long as the various labels have a well-understood meaning.

```c << Move node |p| to the current page; if it is time for a page break, put the nodes following the break back onto the contribution list, and |return| to the user's output routine if there is one >>=
// << If the current page is empty and node |p| is to be deleted, |goto done1|; otherwise use node |p| to update the state of the current page; if this node is an insertion, |goto contribute|; otherwise if this node is not a legal breakpoint, |goto contribute| or |update_heights|; otherwise set |pi| to the penalty associated with this breakpoint >>

// << Check if node |p| is a new champion breakpoint; then if it is time for a page break, prepare for output, and either fire up the user's output routine and |return| or ship out the page and |goto done| >>

if (type(p) < GLUE_NODE || type(p) > KERN_NODE) {
    goto contribute;
}
update_heights:
// << Update the current page measurements with respect to the glue or kern specified by node |p| >>
contribute:
// << Make sure that |page_max_depth| is not exceeded >>
// << Link node |p| into the current page and |goto done| >>
done1:
// << Recycle node |p| >>
done:
```
