# Section 1051

Some operations are allowed only in privileged modes, i.e., in cases that *mode* $>$ *0*.
The *privileged* function is used to detect violations of this rule; it issues an error message and returns *false* if the current *mode* is negative.

```c << Declare action procedures for use by |main_control| >>+=
bool privileged() {
    if (mode > 0) {
        return true;
    }
    else {
        report_illegal_case();
        return false;
    }
}
```
