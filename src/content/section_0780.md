# Section 780

We enter '`\span`' into *eqtb* with *TAB_MARK* as its command code, and with *SPAN_CODE* as the command modifier.
This makes $\TeX$ interpret it essentially the same as an alignment delimiter like '`&`', yet it is
recognizably different when we need to distinguish it from a normal delimiter.
It also turns out to be useful to give a special *CR_CODE* to '`\cr`', and an even larger *CR_CR_CODE* to '`\crcr`'.

The end of a template is represented by two "frozen" control sequences called `\endtemplate`.
The first has the command code *END_TEMPLATE*, which is $>$ *OUTER_CALL*, so it will not easily disappear in the presence of errors.
The *get_x_token* routine converts the first into the second, which has *ENDV* as its command code.

> ![NOTE] 
> String `"endemplate"` is added to the pool.

```c << Read the other strings >>+=
put_string("endtemplate"); // ENDTEMPLATE_STRING: 267
```

```c << Internal strings numbers in the pool >>+=
#define ENDTEMPLATE_STRING 267
```

```c include/constants.h
#define SPAN_CODE          256           // distinct from any character
#define CR_CODE            257           // distinct from |SPAN_CODE| and from any character
#define CR_CR_CODE         (CR_CODE + 1) // this distinguishes \crcr from \cr
#define END_TEMPLATE_TOKEN (CS_TOKEN_FLAG + FROZEN_END_TEMPLATE)
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("span", TAB_MARK, SPAN_CODE);
primitive("cr", CAR_RET, CR_CODE);
text(FROZEN_CR) = str_ptr - 1; // "cr"
eqtb[FROZEN_CR] = eqtb[cur_val];
primitive("crcr", CAR_RET, CR_CR_CODE);
text(FROZEN_END_TEMPLATE) = ENDTEMPLATE_STRING;
text(FROZEN_ENDV) = ENDTEMPLATE_STRING;
eq_type(FROZEN_ENDV) = ENDV;
equiv(FROZEN_ENDV) = NULL_LIST;
eq_level(FROZEN_ENDV) = LEVEL_ONE;
eqtb[FROZEN_END_TEMPLATE] = eqtb[FROZEN_ENDV];
eq_type(FROZEN_END_TEMPLATE) = END_TEMPLATE;
```
