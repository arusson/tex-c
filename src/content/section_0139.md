# Section 139

A new rule node is delivered by the *new_rule* function.
It makes all the dimensions "running", so you have to change the ones that are not allowed to run.

```c datastructures/nodes.c
pointer new_rule() {
    pointer p = get_node(RULE_NODE_SIZE); // the new node
    type(p) = RULE_NODE;
    subtype(p) = 0; // the |subtype| is not used
    width(p) = NULL_FLAG;
    depth(p) = NULL_FLAG;
    height(p) = NULL_FLAG;
    return p;
}
```
