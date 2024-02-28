# Section 863

The '**loop**' in the following code is performed at most thrice per call of *line_break*, since it is actually a pass over the entire paragraph.

```c << Find optimal breakpoints >>=
threshold = pretolerance;
if (threshold >= 0) {
#ifdef STAT
    if (tracing_paragraphs > 0) {
        begin_diagnostic();
        print_nl("@firstpass");
    } 
#endif
    second_pass = false;
    final_pass = false;
}
else {
    threshold = tolerance;
    second_pass = true;
    final_pass = (emergency_stretch <= 0);
 
#ifdef STAT
    if (tracing_paragraphs > 0) {
        begin_diagnostic();
    }
#endif
}
while(true) {
    if (threshold > INF_BAD) {
        threshold = INF_BAD;
    }
    if (second_pass) {
        // << Initialize for hyphenating a paragraph >>
    }
    // << Create an active breakpoint representing the beginning of the paragraph >>
    cur_p = link(TEMP_HEAD);
    auto_breaking = true;
    prev_p = cur_p; // glue at beginning is not a legal breakpoint
    while (cur_p != null && link(ACTIVE) != LAST_ACTIVE) {
        // << Call |try_break| if |cur_p| is a legal breakpoint; on the second pass, also try to hyphenate the next word, if |cur_p| is a glue node; then advance |cur_p| to the next node of the paragraph that could possibly be a legal breakpoint >>
    }
    if (cur_p == null) {
        // << Try the final line break at the end of the paragraph, and |goto done| if the desired breakpoints have been found >>
    }
    // << Clean up the memory by removing the break nodes >>
    if (!second_pass) {
#ifdef STAT
        if (tracing_paragraphs > 0) {
            print_nl("@secondpass");
        }
#endif
        threshold = tolerance;
        second_pass = true;
        final_pass = (emergency_stretch <= 0);
    } // if at first you don't succeed, \dots
    else {
#ifdef STAT
        if (tracing_paragraphs > 0) {
            print_nl("@emergencypass");
        }
#endif
        background[2] += emergency_stretch;
        final_pass = true;
    }
}
done:
#ifdef STAT
if (tracing_paragraphs > 0) {
    end_diagnostic(true);
    normalize_selector();
}
#endif
```
