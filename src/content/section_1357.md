# Section 1357

```c << Make a partial copy of the whatsit node |p| and make |r| point to it; set |words| to the number of initial words not yet copied >>=
switch (subtype(p)) {
case OPEN_NODE:
    r = get_node(OPEN_NODE_SIZE);
    words = OPEN_NODE_SIZE;
    break;

case WRITE_NODE:
case SPECIAL_NODE:
    r = get_node(WRITE_NODE_SIZE);
    add_token_ref(write_tokens(p));
    words = WRITE_NODE_SIZE;
    break;

case CLOSE_NODE:
case LANGUAGE_NODE:
    r = get_node(SMALL_NODE_SIZE);
    words = SMALL_NODE_SIZE;
    break;

default:
    confusion("ext2");
}
```
