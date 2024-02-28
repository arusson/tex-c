# Section 1168

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case VCENTER_GROUP:
    end_graf();
    unsave();
    save_ptr -= 2;
    p = vpack(link(head), saved(1), saved(0));
    pop_nest();
    tail_append(new_noad());
    type(tail) = VCENTER_NOAD;
    math_type(nucleus(tail)) = SUB_BOX;
    info(nucleus(tail)) = p;
    break;
```
