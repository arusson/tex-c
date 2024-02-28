# Section 903

If hyphens are in fact going to be inserted, $\TeX$ first deletes the subsequence of nodes between *ha* and&nbsp;*hb*.
An attempt is made to preserve the effect that implicit boundary characters and punctuation marks had on ligatures inside the hyphenated word, by storing a left boundary or preceding character in *hu[0]* and by storing a possible right boundary in *bchar*.
We set *j &larr; 0* if *hu[0]* is to be part of the reconstruction; otherwise *j &larr; 1*.
The variable *s* will point to the tail of the current hlist, and *q* will point to the node following *hb*, so that things can be hooked up after we reconstitute the hyphenated word.

```c << Replace nodes |ha..hb| by a sequence of nodes that includes the discretionary hyphens >>=
q = link(hb);
link(hb) = null;
r = link(ha);
link(ha) = null;
bchar = hyf_bchar;
if (is_char_node(ha)) {
    if (font(ha) != hf) {
        goto found2;
    }
    else {
        init_list = ha;
        init_lig = false;
        hu[0] = character(ha);
    }
}
else if (type(ha) == LIGATURE_NODE) {
    if (font(lig_char(ha)) != hf) {
        goto found2;
    }
    else {
        init_list = lig_ptr(ha);
        init_lig = true;
        init_lft = (subtype(ha) > 1);
        hu[0] = character(lig_char(ha));
        if (init_list == null && init_lft) {
            hu[0] = 256;
            init_lig = false;
        } // in this case a ligature will be reconstructed from scratch
        free_node(ha, SMALL_NODE_SIZE);
    }
}
else {
    // no punctuation found; look for left boundary
    if (!is_char_node(r) && type(r) == LIGATURE_NODE && subtype(r) > 1) {
        goto found2;
    }
    j = 1;
    s = ha;
    init_list = null;
    goto common_ending;
}
s = cur_p; // we have |cur_p != ha| because |type(cur_p) = GLUE_NODE|
while (link(s) != ha) {
    s = link(s);
}
j = 0;
goto common_ending;
found2:
s = ha;
j = 0;
hu[0] = 256;
init_lig = false;
init_list = null;
common_ending:
flush_node_list(r);
// << Reconstitute nodes for the hyphenated word, inserting discretionary hyphens >>
flush_list(init_list);
```
