# Section 902

$\TeX$ will never insert a hyphen that has fewer than `\lefthyphenmin` letters before it or fewer than `\righthyphenmin` after it; hence, a short word has comparatively little chance of being hyphenated.
If no hyphens have been found, we can save time by not having to make any changes to the paragraph.

```c << If no hyphens were found, |return| >>=
for(j = l_hyf; j <= hn - r_hyf; j++) {
    if (odd(hyf[j])) {
        goto found1;
    }
}
return;
found1:
```
