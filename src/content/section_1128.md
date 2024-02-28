# Section 1128

```c << Express consternation over the fact that no alignment is in progress >>=
print_err("Misplaced ");
print_cmd_chr(cur_cmd, cur_chr);
if (cur_tok == TAB_TOKEN + '&') {
    help6("I can't figure out why you would want to use a tab mark")
        ("here. If you just want an ampersand, the remedy is")
        ("simple: Just type `I\\&' now. But if some right brace")
        ("up above has ended a previous alignment prematurely,")
        ("you're probably due for more error messages, and you")
        ("might try typing `S' now just to see what is salvageable.");
}
else {
    help5("I can't figure out why you would want to use a tab mark")
        ("or \\cr or \\span just now. If something like a right brace")
        ("up above has ended a previous alignment prematurely,")
        ("you're probably due for more error messages, and you")
        ("might try typing `S' now just to see what is salvageable.");
}
error();
```
