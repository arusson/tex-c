# Section 609

When the *movement* procedure gets to the label *found*, the value of *info(p)* will be either *Y_HERE* or *Z_HERE*.
If it is, say, *Y_HERE*, the procedure generates a *Y0* command (or a *W0* command), and marks all *info* fields between *q* and *p* so that *Y* is not OK in that range.

```c << Generate a |Y0| or |Z0| command in order to reuse a previous appearance of |w| >>=
info(q) = info(p);
if (info(q) == Y_HERE) {
    dvi_out(o + Y0 - DOWN1); // |Y0| or |W0|
    while (link(q) != p) {
        q = link(q);
        switch (info(q)) {
        case YZ_OK:
            info(q) = Z_OK;
            break;
        
        case Y_OK:
            info(q) = D_FIXED;
            break;
        
        default:
            do_nothing;
        }
    }
}
else {
    dvi_out(o + Z0 - DOWN1); // |Z0| or |X0|
    while (link(q) != p) {
        q = link(q);
        switch (info(q)) {
        case YZ_OK:
            info(q) = Y_OK;
            break;
        
        case Z_OK:
            info(q) = D_FIXED;
            break;
        
        default:
            do_nothing;
        }
    }
}
```
