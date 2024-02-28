# Section 1339

```c << Numbered cases for |debug_help| >>=
case 1:
    print_word(mem[n]);
    break; // display |mem[n]| in all forms

case 2:
    print_int(info(n));
    break;

case 3:
    print_int(link(n));
    break;

case 4:
    print_word(eqtb[n]);
    break;

case 5:
    print_word(font_info[n]);
    break;

case 6:
    print_word(save_stack[n]);
    break;

case 7:
    // show a box, abbreviated by |show_box_depth| and |show_box_breadth|
    show_box(n);
    break;
   
case 8:
    // show a box in its entirety
    breadth_max = 10000;
    depth_threshold = POOL_SIZE - pool_ptr - 10;
    show_node_list(n); 
    break;

case 9:
    show_token_list(n, null, 1000);
    break;

case 10:
    slow_print(n);
    break;

case 11:
    // check wellformedness; print new busy locations if |n > 0|
    check_mem(n > 0);
    break;

case 12:
    // look for pointers to |n|
    search_mem(n);
    break;

case 13:
    err = scanf("%d", &l);
    if (err != 1) {
        print("?");
        continue;
    }
    print_cmd_chr(n, l);
    break;

case 14:
    for(k = 0; k <= n; k++) {
        print_strnumber(buffer[k]);
    }
    break;

case 15:
    font_in_short_display = NULL_FONT;
    short_display(n);
    break;

case 16:
    panicking = !panicking;
    break;
```
