# Section 1072

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case HMOVE:
    if (chr_code == 1) {
        print_esc("moveleft");
    }
    else {
        print_esc("moveright");
    }
    break;

case VMOVE:
    if (chr_code == 1) {
        print_esc("raise");
    }
    else {
        print_esc("lower");
    }
    break;

case MAKE_BOX:
    switch (chr_code) {
    case BOX_CODE:
        print_esc("box");
        break;
  
    case COPY_CODE:
        print_esc("copy");
        break;
    
    case LAST_BOX_CODE:
        print_esc("lastbox");
        break;
  
    case VSPLIT_CODE:
        print_esc("vsplit");
        break;
  
    case VTOP_CODE:
        print_esc("vtop");
        break;
  
    case VTOP_CODE + VMODE:
        print_esc("vbox");
        break;
    
    default:
        print_esc("hbox");
    }
    break;

case LEADER_SHIP:
    if (chr_code == A_LEADERS) {
        print_esc("leaders");
    }
    else if (chr_code == C_LEADERS) {
        print_esc("cleaders");
    }
    else if (chr_code == X_LEADERS) {
        print_esc("xleaders");
    }
    else {
        print_esc("shipout");
    }
    break;
```
