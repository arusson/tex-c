# Section 111

Here are the inequalities that the quarterword and halfword values must satisfy (or rather, the inequalities that they mustn't satisfy):

```c << Check the "constant" values for consistency >>+=
#ifdef INIT
if (MEM_MIN != MEM_BOT || MEM_MAX != MEM_TOP) {
    bad = 10;
}
#endif
if (MEM_MIN > MEM_BOT || MEM_MAX < MEM_TOP) {
    bad = 10;
}
if (MIN_QUARTERWORD > 0 || MAX_QUARTERWORD < 127) {
    bad = 11;
}
if (MIN_HALFWORD > 0 || MAX_HALFWORD < 32767) {
    bad = 12;
}
if (MIN_QUARTERWORD < MIN_HALFWORD || MAX_QUARTERWORD > MAX_HALFWORD) {
    bad = 13;
}
if (MEM_MIN < MIN_HALFWORD
    || MEM_MAX >= MAX_HALFWORD
    || MEM_BOT - MEM_MIN > MAX_HALFWORD + 1)
{
    bad = 14;
}
if (FONT_BASE < MIN_QUARTERWORD || FONT_MAX > MAX_QUARTERWORD) {
    bad = 15;
}
if (FONT_MAX > FONT_BASE + 256) {
    bad = 16;
}
if (SAVE_SIZE > MAX_HALFWORD || MAX_STRINGS > MAX_HALFWORD) {
    bad = 17;
}
if (BUF_SIZE > MAX_HALFWORD) {
    bad = 18;
}
if (MAX_QUARTERWORD - MIN_QUARTERWORD < 255) {
    bad = 19;
}
```
