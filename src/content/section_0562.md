# Section 562

```c << Read and check the font data; |abort| if the TFM file is malformed; if there's no room for this font, say so and |goto done|; otherwise |incr(font_ptr)| and |goto done| >>=
// << Open |tfm_file| for input >>
// << Read the TFM size fields >>
// << Use size fields to allocate font information >>
// << Read the TFM header >>
// << Read character data >>
// << Read box dimensions >>
// << Read ligature/kern program >>
// << Read extensible character recipes >>
// << Read font parameters >>
// << Make final adjustments and |goto done| >>
```
