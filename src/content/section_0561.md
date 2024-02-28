# Section 561

There are programs called `TFtoPL` and `PLtoTF` that convert between the `TFM` format and a symbolic property-list format that can be easily edited.
These programs contain extensive diagnostic information, so $\TeX$ does not have to bother giving
precise details about why it rejects a particular `TFM` file.

```c include/font_metric.h
#define start_font_error_message                  \
    do {                                          \
        print_err("Font ");                       \
        sprint_cs(u);                             \
        print_char('=');                          \
        print_file_name(nom, aire, EMPTY_STRING); \
        if (s >= 0) {                             \
            print(" at ");                        \
            print_scaled(s);                      \
            print("pt");                          \
        }                                         \
        else if (s != -1000) {                    \
            print(" scaled ");                    \
            print_int(-s);                        \
        }                                         \
    } while (0)
```

```c << Report that the font won't be loaded >>=
start_font_error_message;
if (file_opened) {
    print(" not loadable: Bad metric (TFM) file");
}
else {
    print(" not loadable: Metric (TFM) file not found");
}
help5("I wasn't able to read the size data for this font,")
    ("so I will ignore the font specification.")
    ("[Wizards can fix TFM files using TFtoPL/PLtoTF.]")
    ("You might try inserting a different font spec;")
    ("e.g., type `I\\font<same font id>=<substitute font name>'.");
error();
```
