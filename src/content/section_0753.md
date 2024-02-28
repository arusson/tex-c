# Section 753

Note that a ligature between an *ORD_NOAD* and another kind of noad is replaced by an *ORD_NOAD*, when the two noads collapse into one.
But we could make a parenthesis (say) change shape when it follows certain letters.
Presumably a font designer will define such ligatures only when this convention makes sense.

```c << If instruction |cur_i| is a kern with |cur_c|, attach the kern after |q|; or if it is a ligature with |cur_c|, combine noads |q| and |p| appropriately; then |return| if the cursor has moved past a noad, or |goto restart| >>=
if (next_char(cur_i) == cur_c && skip_byte(cur_i) <= STOP_FLAG) {
    if (op_byte(cur_i) >= KERN_FLAG) {
        p = new_kern(char_kern(cur_f, cur_i));
        link(p) = link(q);
        link(q) = p;
        return;
    }
    check_interrupt; // allow a way out of infinite ligature loop
    switch (op_byte(cur_i)) {
    case 1:
    case 5:
        // =:|, =:|>
        character(nucleus(q)) = rem_byte(cur_i);
        break;
    
    case 2:
    case 6:
        // |=:, |=:>
        character(nucleus(p)) = rem_byte(cur_i);
        break;

    case 3:
    case 7:
    case 11: 
        // |=:|, |=:|>, |=:|>>
        r = new_noad();
        character(nucleus(r)) = rem_byte(cur_i);
        fam(nucleus(r)) = fam(nucleus(q));
        link(q) = r;
        link(r) = p;
        if (op_byte(cur_i) < 11) {
            math_type(nucleus(r)) = MATH_CHAR;
        }
        else {
            // prevent combination
            math_type(nucleus(r)) = MATH_TEXT_CHAR;
        }
        break;
    
    default:
        // =:
        link(q) = link(p);
        character(nucleus(q)) = rem_byte(cur_i);
        mem[subscr(q)] = mem[subscr(p)];
        mem[supscr(q)] = mem[supscr(p)];
        free_node(p, NOAD_SIZE);   
    }
    if (op_byte(cur_i) > 3) {
        return;
    }
    math_type(nucleus(q)) = MATH_CHAR;
    goto restart;
}
```
