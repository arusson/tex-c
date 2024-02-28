# Section 987

Here is a procedure that is called when the *page_contents* is changing from *EMPTY* to *INSERTS_ONLY* or *BOX_THERE*.

```c include/builder.h
#define set_page_so_far_zero(X) page_so_far[(X)] = 0
```

```c builder/page_builder.c
// << Start file |page_builder.c| >>

void freeze_page_specs(small_number s) {
    page_contents = s;
    page_goal = vsize;
    page_max_depth = max_depth;
    page_depth = 0;
    do_all_six(set_page_so_far_zero);
    least_page_cost = AWFUL_BAD;
#ifdef STAT
    if (tracing_pages > 0) {
        begin_diagnostic();
        print_nl("\%\% goal height=");
        print_scaled(page_goal);
        print(", max depth=");
        print_scaled(page_max_depth);
        end_diagnostic(false);
    }
#endif
}
```
