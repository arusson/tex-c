# Section 1048

When erroneous situations arise, $\TeX$ usually issues an error message specific to the particular error.
For example, '`\noalign`' should not appear in any mode, since it is recognized by the *align_peek* routine in all of its legitimate appearances; a special error message is given when '`\noalign`' occurs elsewhere.
But sometimes the most appropriate error message is simply that the user is not allowed to do what he or she has attempted.
For example, '`\moveleft`' is allowed only in vertical mode, and '`\lower`' only in non-vertical modes.
Such cases are enumerated here and in the other sections referred to under 'See also $\dots$.'

```c << Forbidden cases detected in |main_control| >>=
case VMODE + VMOVE:
case HMODE + HMOVE:
case MMODE + HMOVE:
any_mode(LAST_ITEM):
```
