# Section 224

Region 3 of *eqtb* contains the 256 `\skip` registers, as well as the glue parameters defined here.
It is important that the "muskip" parameters have larger numbers than the others.

> ![NOTE]
> The  ⟨ Current *mem* equivalent of glue parameter number *n* 224 ⟩ is directly included in sections [152](./part10.md#section-152) and [154](./part10.md#section-154).

```c include/constants.h
#define LINE_SKIP_CODE                0      // interline glue if |baseline_skip| is infeasible
#define BASELINE_SKIP_CODE            1      // desired glue between baselines
#define PAR_SKIP_CODE                 2      // extra glue just above a paragraph
#define ABOVE_DISPLAY_SKIP_CODE       3      // extra glue just above displayed math
#define BELOW_DISPLAY_SKIP_CODE       4      // extra glue just below displayed math
#define ABOVE_DISPLAY_SHORT_SKIP_CODE 5      // glue above displayed math following short lines
#define BELOW_DISPLAY_SHORT_SKIP_CODE 6      // glue below displayed math following short lines
#define LEFT_SKIP_CODE                7      // glue at left of justified lines
#define RIGHT_SKIP_CODE               8      // glue at right of justified lines
#define TOP_SKIP_CODE                 9      // glue at top of main pages
#define SPLIT_TOP_SKIP_CODE           10     // glue at top of split pages
#define TAB_SKIP_CODE                 11     // glue between aligned entries
#define SPACE_SKIP_CODE               12     // glue between words (if not |ZERO_GLUE|)
#define XSPACE_SKIP_CODE              13     // glue after sentences (if not |ZERO_GLUE|)
#define PAR_FILL_SKIP_CODE            14     // glue on last line of paragraph
#define THIN_MU_SKIP_CODE             15     // thin space in math formula
#define MED_MU_SKIP_CODE              16     // medium space in math formula
#define THICK_MU_SKIP_CODE            17     // thick space in math formula
#define GLUE_PARS                     18     // total number of glue parameters
#define SKIP_BASE    (GLUE_BASE + GLUE_PARS) // table of 256 "skip" registers
#define MU_SKIP_BASE (SKIP_BASE + 256)       // table of 256 "muskip" registers
#define LOCAL_BASE   (MU_SKIP_BASE + 256)    // beginning of region 4
```

```c include/datastructures.h
#define skip(X)     equiv(SKIP_BASE + (X))    // |mem| location of glue specification
#define mu_skip(X)  equiv(MU_SKIP_BASE + (X)) // |mem| location of math glue spec
#define glue_par(X) equiv(GLUE_BASE + (X))    // |mem| location of glue specification

#define line_skip                glue_par(LINE_SKIP_CODE)
#define baseline_skip            glue_par(BASELINE_SKIP_CODE)
#define par_skip                 glue_par(PAR_SKIP_CODE)
#define above_display_skip       glue_par(ABOVE_DISPLAY_SKIP_CODE)
#define below_display_skip       glue_par(BELOW_DISPLAY_SKIP_CODE)
#define above_display_short_skip glue_par(ABOVE_DISPLAY_SHORT_SKIP_CODE)
#define below_display_short_skip glue_par(BELOW_DISPLAY_SHORT_SKIP_CODE)
#define left_skip                glue_par(LEFT_SKIP_CODE)
#define right_skip               glue_par(RIGHT_SKIP_CODE)
#define top_skip                 glue_par(TOP_SKIP_CODE)
#define split_top_skip           glue_par(SPLIT_TOP_SKIP_CODE)
#define tab_skip                 glue_par(TAB_SKIP_CODE)
#define space_skip               glue_par(SPACE_SKIP_CODE)
#define xspace_skip              glue_par(XSPACE_SKIP_CODE)
#define par_fill_skip            glue_par(PAR_FILL_SKIP_CODE)
#define thin_mu_skip             glue_par(THIN_MU_SKIP_CODE)
#define med_mu_skip              glue_par(MED_MU_SKIP_CODE)
#define thick_mu_skip            glue_par(THICK_MU_SKIP_CODE)
```
