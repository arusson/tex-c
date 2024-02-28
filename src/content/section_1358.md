# Section 1358

```c << Wipe out the whatsit node |p| and |goto done| >>=
switch (subtype(p)) {
case OPEN_NODE:
    free_node(p, OPEN_NODE_SIZE);
    break;

case WRITE_NODE:
case SPECIAL_NODE:
    delete_token_ref(write_tokens(p));
    free_node(p, WRITE_NODE_SIZE);
    goto done;

case CLOSE_NODE:
case LANGUAGE_NODE:
    free_node(p, SMALL_NODE_SIZE);
    break;

default:
    confusion("ext3");
}
goto done;
```
