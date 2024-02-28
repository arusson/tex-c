# Section 854

During the final pass, we dare not lose all active nodes, lest we lose touch with the line breaks already found.
The code shown here makes sure that such a catastrophe does not happen, by permitting overfull boxes as a last resort.
This particular part of $\TeX$ was a source of several subtle bugs before the correct program logic was finally discovered; readers who seek to "improve" $\TeX$ should therefore think thrice before daring to make any changes here.

```c << Prepare to deactivate node |r|, and |goto deactivate| unless there is a reason to consider lines of text from |r| to |cur_p| >>=
if (final_pass
    && minimum_demerits == AWFUL_BAD
    && link(r) == LAST_ACTIVE
    && prev_r == ACTIVE)
{
    artificial_demerits = true; // set demerits zero, this break is forced
}
else if (b > threshold) {
    goto deactivate;
}
node_r_stays_active = false;
```
