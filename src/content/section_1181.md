# Section 1181

```c math/math_lists.c
void math_fraction() {
    small_number c; // the type of generalized fraction we are scanning
    c = cur_chr;
    if (incompleat_noad != null) {
        // << Ignore the fraction operation and complain about this ambiguous case >>
    }
    else {
        incompleat_noad = get_node(FRACTION_NOAD_SIZE);
        type(incompleat_noad) = FRACTION_NOAD;
        subtype(incompleat_noad) = NORMAL;
        math_type(numerator(incompleat_noad)) = SUB_MLIST;
        info(numerator(incompleat_noad)) = link(head);
        mem[denominator(incompleat_noad)] = empty_field;
        mem[left_delimiter(incompleat_noad)] = null_delimiter;
        mem[right_delimiter(incompleat_noad)] = null_delimiter;
        link(head) = null;
        tail = head;
        // << Use code |c| to distinguish between generalized fractions >>
    }
}
```
