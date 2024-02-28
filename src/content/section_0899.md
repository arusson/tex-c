# Section 899

```c << Check that the nodes following |hb| permit hyphenation and that at least |l_hyf + r_hyf| letters have been found, otherwise |goto done1| >>=
if (hn < l_hyf + r_hyf) {
    goto done1; // |l_hyf| and |r_hyf| are >= 1
}
while(true) {
    if (!(is_char_node(s))) {
        switch (type(s)) {
        case LIGATURE_NODE:
            do_nothing;
            break;
        
        case KERN_NODE:
            if (subtype(s) != NORMAL) {
                goto done4;
            }
            break;

        case WHATSIT_NODE:
        case GLUE_NODE:
        case PENALTY_NODE:
        case INS_NODE:
        case ADJUST_NODE:
        case MARK_NODE:
            goto done4;
        
        default:
            goto done1;
        }
    }
    s = link(s);
}
done4:
```
