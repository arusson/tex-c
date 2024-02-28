# Section 1198

We have saved the worst for last: The fussiest part of math mode processing occurs when a displayed formula is being centered and placed with an optional equation number.

```c << Local variables for finishing a displayed formula >>=
pointer b;           // box containing the equation
scaled w;            // width of the equation
scaled z;            // width of the line
scaled e;            // width of equation number
scaled q;            // width of equation number plus space to separate from equation
scaled d;            // displacement of equation in the line
scaled s;            // move the line right this much
small_number g1, g2; // glue parameter codes for before and after
pointer r;           // kern node used to position the display
pointer t;           // tail of adjustment list
```
