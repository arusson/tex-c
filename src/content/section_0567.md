# Section 567

```c << Apologize for not loading the font, |goto done| >>=
start_font_error_message;
print(" not loaded: Not enough room left");
help4("I'm afraid I won't be able to make use of this font,")
    ("because my memory for character-size data is too small.")
    ("If you're really stuck, ask a wizard to enlarge me.")
    ("Or maybe try `I\\font<same font id>=<name of loaded font>'.");
error();
goto done;
```
