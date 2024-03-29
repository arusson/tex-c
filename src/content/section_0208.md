# Section 208

Next are the ordinary run-of-the-mill command codes.
Codes that are *MIN_INTERNAL* or more represent internal quantities that might be expanded by '`\the`'.

```c include/constants.h
#define CHAR_NUM                 16 // character specified numerically (\char)
#define MATH_CHAR_NUM            17 // explicit math code (\mathchar)
#define MARK                     18 // mark definition (\mark)
#define XRAY                     19 // peek inside of TeX (\show, \showbox, etc.)
#define MAKE_BOX                 20 // make a box (\box, \copy, \hbox, etc.)
#define HMOVE                    21 // horizontal motion (\moveleft, \moveright)
#define VMOVE                    22 // vertical motion (\raise, \lower)
#define UN_HBOX                  23 // unglue a box (\unhbox, \unhcopy)
#define UN_VBOX                  24 // unglue a box (\unvbox, \unvcopy)
#define REMOVE_ITEM              25 // nullify last item (\unpenalty, \unkern, \unskip)
#define HSKIP                    26 // horizontal glue (\hskip, \hfil, etc.)
#define VSKIP                    27 // vertical glue (\vskip, \vfil, etc.)
#define MSKIP                    28 // math glue (\mskip)
#define KERN                     29 // fixed space (\kern)
#define MKERN                    30 // math kern (\mkern)
#define LEADER_SHIP              31 // use a box (\shipout, \leaders, etc.)
#define HALIGN                   32 // horizontal table alignment (\halign)
#define VALIGN                   33 // vertical table alignment (\valign)
#define NO_ALIGN                 34 // temporary escape from alignment (\noalign)
#define VRULE                    35 // vertical rule (\vrule)
#define HRULE                    36 // horizontal rule (\hrule)
#define INSERT                   37 // vlist inserted in box (\insert)
#define VADJUST                  38 // vlist inserted in enclosing paragraph (\vadjust)
#define IGNORE_SPACES            39 // gobble |spacer| tokens (\ignorespaces)
#define AFTER_ASSIGNMENT         40 // save till assignment is done (\afterassignment)
#define AFTER_GROUP              41 // save till group is done (\aftergroup)
#define BREAK_PENALTY            42 // additional badness (\penalty)
#define START_PAR                43 // begin paragraph (\indent, \noindent)
#define ITAL_CORR                44 // italic correction (\/)
#define ACCENT                   45 // attach accent in text (\accent)
#define MATH_ACCENT              46 // attach accent in math (\mathaccent)
#define DISCRETIONARY            47 // discretionary texts (\-, \discretionary)
#define EQ_NO                    48 // equation number (\eqno, \leqno)
#define LEFT_RIGHT               49 // variable delimiter (\left, \right)
#define MATH_COMP                50 // component of formula (\mathbin, etc.)
#define LIMIT_SWITCH             51 // diddle limit conventions (\displaylimits, etc.)
#define ABOVE                    52 // generalized fraction (\above, \atop, etc.)
#define MATH_STYLE               53 // style specification (\displaystyle, etc.)
#define MATH_CHOICE              54 // choice specification (\mathchoice)
#define NON_SCRIPT               55 // conditional math glue (\nonscript)
#define VCENTER                  56 // vertically center a vbox (\vcenter)
#define CASE_SHIFT               57 // force specific case (\lowercase, \uppercase)
#define MESSAGE                  58 // send to user (\message, \errmessage)
#define EXTENSION                59 // extensions to \TeX\ (\write, \special, etc.)
#define IN_STREAM                60 // files for reading (\openin, \closein)
#define BEGIN_GROUP              61 // begin local grouping (\begingroup)
#define END_GROUP                62 // end local grouping (\endgroup)
#define OMIT                     63 // omit alignment template (\omit)
#define EX_SPACE                 64 // explicit space (\ )
#define NO_BOUNDARY              65 // suppress boundary ligatures (\noboundary)
#define RADICAL                  66 // square root and similar signs (\radical)
#define END_CS_NAME              67 // end control sequence (\endcsname)
#define MIN_INTERNAL             68 // the smallest code that can follow \the
#define CHAR_GIVEN               68 // character code defined by \chardef
#define MATH_GIVEN               69 // math code defined by \mathchardef
#define LAST_ITEM                70 // most recent item (\lastpenalty, \lastkern, \lastskip)
#define MAX_NON_PREFIXED_COMMAND 70 // largest command code that can't be \global
```
