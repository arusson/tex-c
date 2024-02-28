# Section 1109

The *UN_HBOX* and *UN_VBOX* commands unwrap one of the 256 current boxes.

```c << Cases of |main_control| that build boxes and lists >>+=
case VMODE + UN_VBOX:
case HMODE + UN_HBOX:
case MMODE + UN_HBOX:
    unpackage();
    break;
```
