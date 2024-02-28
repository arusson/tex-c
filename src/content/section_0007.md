# Section 7

Some of the code below is intended to be used only when diagnosing the strange behavior that sometimes occurs when $\TeX$ is being installed or when system wizards are fooling around with $\TeX$ without quite knowing what they are doing.
Such code will not normally be compiled; it is delimited by the codewords '**debug** $\ldots$ **gubed**', with apologies to people who wish to preserve the purity of English.

Similarly, there is some conditional code delimited by '**stat** $\ldots$ **tats**' that is intended for use when statistics are to be kept about $\TeX$'s memory usage.
The **stat** $\ldots$ **tats** code also implements diagnostic information for `\tracingparagraphs`, `\tracingpages`, and `\tracingrestores`.

> ![NOTE]
> Macro preprocessor`#ifdef` is used to define those blocks:
> - `#ifdef DEBUG` for **debug**;
> - `#ifdef STAT` for **stat**;
> - The closing is only `#endif`.
> The flags `-DDEBUG` and `-DSTAT` can be used to activate them at compilation time (see the [Makefile](./part53.md#section-1383)).
