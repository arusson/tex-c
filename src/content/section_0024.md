# Section 24

The following system-independent code makes the *XORD* array contain a suitable inverse to the information in *XCHR*.
Note that if *XCHR[i] = XCHR[j]* where *i* $<$ *j* $<$ *127*, the value of *XORD[XCHR[i]]* will turn out to be *j* or more;
hence, standard ASCII code numbers will be used instead of codes below 32 in case there is a coincidence.

> ![NOTE]
> Done at declaration in section [20](./part02.md#section-20).
