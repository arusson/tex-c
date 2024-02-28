# Section 21

Since we are assuming that our Pascal system is able to read and write the visible characters of standard ASCII (although not necessarily using the ASCII codes to represent them), the following assignment statements initialize the standard part of the *XCHR* array properly, without needing any system-dependent changes.
On the other hand, it is possible to implement $\TeX$ with less complete character sets, and in such cases it will be necessary to change something here.

> ![NOTE]
> Done as declaration of `XORD` and `XCHR` in previous section.
> To keep the number of this section in blocks ⟨&nbsp;Set initial values of key variables [21](./part02.md#section-21)&nbsp;⟩ from the original code, an empty fenced block is defined.

```c << Set initial values of key variables >>=
```