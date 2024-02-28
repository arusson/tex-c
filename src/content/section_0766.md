# Section 766

```c << Append inter-element spacing based on |r_type| and |t| >>=
if (r_type > 0) {
    // not the first noad
    switch (MATH_SPACING[r_type * 8 + t - 9 * ORD_NOAD]) {
    case '0':
        x = 0;
        break;
    
    case '1':
        if (cur_style < SCRIPT_STYLE) {
            x = THIN_MU_SKIP_CODE;
        }
        else {
            x = 0;
        }
        break;
    
    case '2':
        x = THIN_MU_SKIP_CODE;
        break;
    
    case '3':
        if (cur_style < SCRIPT_STYLE) {
            x = MED_MU_SKIP_CODE;
        }
        else {
            x = 0;
        }
        break;
    
    case '4':
        if (cur_style < SCRIPT_STYLE) {
            x = THICK_MU_SKIP_CODE;
        }
        else {
            x = 0;
        }
        break;
    
    default:
        confusion("mlist4");
    }

    if (x != 0) {
        y = math_glue(glue_par(x), cur_mu);
        z = new_glue(y);
        glue_ref_count(y) = null;
        link(p) = z;
        p = z;
        subtype(z) = x + 1; // store a symbolic subtype
    }
}
```
