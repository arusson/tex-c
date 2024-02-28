# Section 202

Now we are ready to delete any node list, recursively.
In practice, the nodes deleted are usually charnodes (about 2/3 of the time), and they are glue nodes in about half of the remaining cases.

```c datastructures/memory.c
// erase list of nodes starting at |p|
void flush_node_list(pointer p) {
    pointer q; // successor to node |p|
    while (p != null) {
        q = link(p);
        if (is_char_node(p)) {
            free_avail(p);
        }
        else  {
            switch(type(p)) {
            case HLIST_NODE:
            case VLIST_NODE:
            case UNSET_NODE:
                flush_node_list(list_ptr(p));
                free_node(p, BOX_NODE_SIZE);
                goto done;
            
            case RULE_NODE:
                free_node(p, RULE_NODE_SIZE);
                goto done;
            
            case INS_NODE:
                flush_node_list(ins_ptr(p));
                delete_glue_ref(split_top_ptr(p));
                free_node(p, INS_NODE_SIZE);
                goto done;
            
            case WHATSIT_NODE:
                // << Wipe out the whatsit node |p| and |goto done| >>
            
            case GLUE_NODE:
                fast_delete_glue_ref(glue_ptr(p));
                if (leader_ptr(p) != null) {
                    flush_node_list(leader_ptr(p));
                }
                break;
            
            case KERN_NODE:
            case MATH_NODE:
            case PENALTY_NODE:
                do_nothing;
                break;
            
            case LIGATURE_NODE:
                flush_node_list(lig_ptr(p));
                break;
            
            case MARK_NODE:
                delete_token_ref(mark_ptr(p));
                break;
            
            case DISC_NODE:
                flush_node_list(pre_break(p));
                flush_node_list(post_break(p));
                break;
            
            case ADJUST_NODE:
                flush_node_list(adjust_ptr(p));
                break;
            
            // << Cases of |flush_node_list| that arise in mlists only >>

            default:
                confusion("flushing");
            }
            free_node(p, SMALL_NODE_SIZE);
done:
        }
        p = q;
    }
}
```
