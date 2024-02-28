# Section 241

The following procedure, which is called just before $\TeX$ initializes its input and output, establishes the initial values of the date and time.
Since standard Pascal cannot provide such information, something special is needed.
The program here simply assumes that suitable values appear in the global variables *sys_time*, *sys_day*, *sys_month*, and *sys_year* (which are initialized to noon on 4 July 1776, in case the implementor is careless).

> ![NOTE]
> We make use of *localtime* function to get the time from the machine.

```c init_cleanup.c
void fix_date_and_time() {
    time_t rawtime;
    struct tm *data;
    time(&rawtime);
    data = localtime(&rawtime);
    sys_time = data->tm_hour * 60 + data->tm_min;
    sys_day = data->tm_mday;
    sys_month = data->tm_mon + 1;
    sys_year = data->tm_year + 1900;

    time_ = sys_time;  // minutes since midnight
    day = sys_day;     // day of the month
    month = sys_month; // month of the year
    year = sys_year;   // Anno Domini
}
```
