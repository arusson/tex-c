# Section 1026

When the user's output routine finishes, it has constructed a vlist in internal vertical mode, and $\TeX$ will do the following:

```c << Resume the page builder after an output routine has come to an end >>=
if (loc != null
    || (token_type != OUTPUT_TEXT && token_type != BACKED_UP))
{
    // << Recover from an unbalanced output routine >>
}
end_token_list(); // conserve stack space in case more outputs are triggered
end_graf();
unsave();
output_active = false;
insert_penalties = 0;
// << Ensure that box 255 is empty after output >>
if (tail != head) {
    // current list goes after heldover insertions
    link(page_tail) = link(head);
    page_tail = tail;
}
if (link(PAGE_HEAD) != null) {
    // and both go before heldover contributions
    if (link(CONTRIB_HEAD) == null) {
        contrib_tail = page_tail;
    }
    link(page_tail) = link(CONTRIB_HEAD);
    link(CONTRIB_HEAD) = link(PAGE_HEAD);
    link(PAGE_HEAD) = null;
    page_tail = PAGE_HEAD;
}
pop_nest();
build_page();
```
