# Section 742

```c << Swap the subscript and superscript into box |x| >>=
flush_node_list(x);
x = new_noad();
mem[nucleus(x)] = mem[nucleus(q)];
mem[supscr(x)] = mem[supscr(q)];
mem[subscr(x)] = mem[subscr(q)];
mem[supscr(q)] = empty_field;
mem[subscr(q)] = empty_field;
math_type(nucleus(q)) = SUB_MLIST;
info(nucleus(q)) = x;
x = clean_box(nucleus(q), cur_style);
delta += height(x) - h;
h = height(x);
```
