# Section 1030

We shall concentrate first on the inner loop of *main_control*, deferring consideration of the other cases until later.


| | |
|-:|-|
| *big_switch*          | go here to branch on the next token of input;          |
| *main_loop*           | go here to typeset a string of consecutive characters; |
| *main_loop_wrapup*    | go here to finish a character or ligature;             |
| *main_loop_move*      | go here to advance the ligature cursor;                |
| *main_loop_move_lig*  | same, when advancing past a generated ligature;        |
| *main_loop_lookahead* | go here to bring in another character, if any;         |
| *main_lig_loop*       | go here to check for ligatures or kerning;             |
| *append_normal_space* | go here to append a normal space between words.        |

```c builder/chief.c
// << Start file |chief.c| >>

// << Declare action procedures for use by |main_control| >>

// governs TeX's activities
void main_control() {
    int t; // general-purpose temporary variable
    if (every_job != null) {
        begin_token_list(every_job, EVERY_JOB_TEXT);
    }

big_switch:
    get_x_token();

reswitch:
    // << Give diagnostic information, if requested >>
    switch (abs(mode) + cur_cmd) {
    case HMODE + LETTER:
    case HMODE + OTHER_CHAR:
    case HMODE + CHAR_GIVEN:
        goto main_loop;
    
    case HMODE + CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        goto main_loop;
    
    case HMODE + NO_BOUNDARY:
        get_x_token();
        if (cur_cmd == LETTER
            || cur_cmd == OTHER_CHAR
            || cur_cmd == CHAR_GIVEN
            || cur_cmd == CHAR_NUM)
        {
            cancel_boundary = true;
        }
        goto reswitch;

    case HMODE + SPACER:
        if (space_factor == 1000) {
            goto append_normal_space;
        }
        else {
            app_space();
        }
        break;
    
    case HMODE + EX_SPACE:
    case MMODE + EX_SPACE:
        goto append_normal_space;
    
    // << Cases of |main_control| that are not part of the inner loop >>

    } // end of the big |case| statement
    goto big_switch;

main_loop:
    // << Append character |cur_chr| and the following characters (if any) to the current hlist in the current font; |goto reswitch| when a non-character has been fetched >>

append_normal_space:
    // << Append a normal inter-word space to the current list, then |goto big_switch| >>
}
```
