# Section 1049

The *'you_cant'* procedure prints a line saying that the current command is illegal in the current mode; it identifies these things symbolically.

```c builder/chief.c
void you_cant() {
    print_err("You can't use `");
    print_cmd_chr(cur_cmd, cur_chr);
    print("' in ");
    print_mode(mode);
}
```
