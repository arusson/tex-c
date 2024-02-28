# Section 1054

We don't want to leave *main_control* immediately when a *STOP* command is sensed, because it may be necessary to invoke an `\output` routine several times before things really grind to a halt.
(The output routine might even say '`\gdef\end{...}`', to prolong the life of the job.)
Therefore *its_all_over* is *true* only when the current page and contribution list are empty, and when the last output was not a "dead cycle".

```c << Declare action procedures for use by |main_control| >>+=
// do this when \end or \dump occurs
bool its_all_over() {
    if (privileged()) {
        if (PAGE_HEAD == page_tail && head == tail && dead_cycles == 0) {
            return true;
        }
        back_input(); // we will try to end again after ejecting residual material
        tail_append(new_null_box());
        width(tail) = hsize;
        tail_append(new_glue(FILL_GLUE));
        tail_append(new_penalty(-0x40000000));
        build_page(); // append \hbox to \hsize{}\vfill\penalty-'10000000000
    }
    return false;
}
```
