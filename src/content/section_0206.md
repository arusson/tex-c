# Section 206

```c << Case statement to copy different types and set |words| to the number of initial words not yet copied >>=
switch(type(p)) {
case HLIST_NODE:
case VLIST_NODE:
case UNSET_NODE:
    r = get_node(BOX_NODE_SIZE);
    mem[r + 6] = mem[p + 6];
    mem[r + 5] = mem[p + 5]; // copy the last two words
    list_ptr(r) = copy_node_list(list_ptr(p)); // this affects |mem[r+5]|
    words = 5;
    break;

case RULE_NODE:
    r = get_node(RULE_NODE_SIZE);
    words = RULE_NODE_SIZE;
    break;

case INS_NODE:
    r = get_node(INS_NODE_SIZE);
    mem[r + 4] = mem[p + 4];
    add_glue_ref(split_top_ptr(p));
    ins_ptr(r) = copy_node_list(ins_ptr(p)); // this affects |mem[r+4]|
    words = INS_NODE_SIZE - 1;
    break;

case WHATSIT_NODE:
    // << Make a partial copy of the whatsit node |p| and make |r| point to it; set |words| to the number of initial words not yet copied >>
    break;

case GLUE_NODE:
    r = get_node(SMALL_NODE_SIZE);
    add_glue_ref(glue_ptr(p));
    glue_ptr(r) = glue_ptr(p);
    leader_ptr(r) = copy_node_list(leader_ptr(p));
    break;

case KERN_NODE:
case MATH_NODE:
case PENALTY_NODE:
    r = get_node(SMALL_NODE_SIZE);
    words = SMALL_NODE_SIZE;
    break;

case LIGATURE_NODE:
    r = get_node(SMALL_NODE_SIZE);
    mem[lig_char(r)] = mem[lig_char(p)]; // copy font and character
    lig_ptr(r) = copy_node_list(lig_ptr(p));
    break;

case DISC_NODE:
    r = get_node(SMALL_NODE_SIZE);
    pre_break(r) = copy_node_list(pre_break(p));
    post_break(r) = copy_node_list(post_break(p));
    break;

case MARK_NODE:
    r = get_node(SMALL_NODE_SIZE);
    add_token_ref(mark_ptr(p));
    words = SMALL_NODE_SIZE;
    break;

case ADJUST_NODE:
    r = get_node(SMALL_NODE_SIZE);
    adjust_ptr(r) = copy_node_list(adjust_ptr(p));
    // words = 1 = SMALL_NODE_SIZE - 1
    break;

default:
    confusion("copying");
}
```
