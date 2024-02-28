// ~~~ Section 560 ~~~
// ~~~ Start file |font_metric.c|, 1382 ~~~
#include "font_metric.h"
#include "arithmetic.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// input a `TFM` file
internal_font_number read_font_info(pointer u, str_number nom, str_number aire, scaled s) {
    font_index k; // index into |font_info|
    bool file_opened; // was |tfm_file| successfully opened?
    halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np; // sizes of subfiles
    internal_font_number f; // the new font's number
    internal_font_number g; // the number to return
    eight_bits a, b, c, d; // byte variables
    memory_word qw;
    scaled sw; // accumulators
    int bch_label; // left boundary start location, or infinity
    int bchar; // boundary character, or 256
    scaled z; // the design size or the ``at'' size
    int alpha, beta; // auxiliary quantities used in fixed-point multiplication
    int temp; // temporary data for read_sixteen macro
    g = NULL_FONT;
    // ~~~ Read and check the font data; |abort| if the TFM file is malformed; if there's no room for this font, say so and |goto done|; otherwise |incr(font_ptr)| and |goto done|, 562 ~~~
    // ~~~ Open |tfm_file| for input, 563 ~~~
    file_opened = false;
    if (aire == EMPTY_STRING) {
        pack_file_name(nom, TEX_FONT_AREA, TFM_EXT);
    }
    else {
        pack_file_name(nom, aire, TFM_EXT);
    }
    if (!b_open_in(&tfm_file)) {
        abort;
    }
    file_opened = true;
    // ~~~ End section 563 ~~~
    // ~~~ Read the TFM size fields, 565 ~~~
    read_sixteen(lf);
    read_sixteen(lh);
    read_sixteen(bc);
    read_sixteen(ec);
    if (bc > ec + 1 || ec > 255) {
        abort;
    }
    if (bc > 255) {
        // |bc == 256| and |ec == 255|
        bc = 1;
        ec = 0;
    }
    read_sixteen(nw);
    read_sixteen(nh);
    read_sixteen(nd);
    read_sixteen(ni);
    read_sixteen(nl);
    read_sixteen(nk);
    read_sixteen(ne);
    read_sixteen(np);
    if (lf != 6 + lh + (ec - bc + 1) + nw + nh + nd + ni + nl + nk + ne + np) {
        abort;
    }
    if ( nw == 0 || nh == 0 || nd == 0 || ni == 0) {
        abort;
    }
    // ~~~ End section 565 ~~~
    // ~~~ Use size fields to allocate font information, 566 ~~~
    lf = lf - 6 - lh; // |lf| words should be loaded into |font_info|
    if (np < 7) {
        lf += 7 - np; // at least seven parameters will appear
    }
    if (font_ptr == FONT_MAX || fmem_ptr + lf > FONT_MEM_SIZE) {
        // ~~~ Apologize for not loading the font, |goto done|, 567 ~~~
        start_font_error_message;
        print(" not loaded: Not enough room left");
        help4("I'm afraid I won't be able to make use of this font,")
            ("because my memory for character-size data is too small.")
            ("If you're really stuck, ask a wizard to enlarge me.")
            ("Or maybe try `I\\font<same font id>=<name of loaded font>'.");
        error();
        goto done;
        // ~~~ End section 567 ~~~
    }
    f = font_ptr + 1;
    char_base[f] = fmem_ptr - bc;
    width_base[f] = char_base[f] + ec + 1;
    height_base[f] = width_base[f] + nw;
    depth_base[f] = height_base[f] + nh;
    italic_base[f] = depth_base[f] + nd;
    lig_kern_base[f] = italic_base[f] + ni;
    kern_base[f] = lig_kern_base[f] + nl - KERN_BASE_OFFSET;
    exten_base[f] = kern_base[f] + KERN_BASE_OFFSET + nk;
    param_base[f] = exten_base[f] + ne;
    // ~~~ End section 566 ~~~
    // ~~~ Read the TFM header, 568 ~~~
    if (lh < 2) {
        abort;
    }
    store_four_quarters(font_check[f]);
    read_sixteen(z); // this rejects a negative design size
    fget(temp);
    z = z*256 + temp;
    fget(temp);
    z = z*16 + (temp / 16);
    if (z < UNITY) {
        abort;
    }
    while (lh > 2) {
        fget(temp);
        fget(temp);
        fget(temp);
        fget(temp);
        decr(lh); // ignore the rest of the header
    }
    font_dsize[f] = z;
    if (s != -1000) {
      if (s >= 0) {
        z = s;
      }
      else {
        z = xn_over_d(z, -s, 1000);
      }
    }
    font_size[f] = z;
    // ~~~ End section 568 ~~~
    // ~~~ Read character data, 569 ~~~
    for(k = fmem_ptr; k <= width_base[f] - 1; k++) {
        store_four_quarters(font_info[k]);
        if ( a >= nw || b/16 >= nh || b % 16 >= nd || c/4 >= ni) {
            abort;
        }
        switch (c % 4) {
        case LIG_TAG:
            if (d >= nl) {
                abort;
            }
            break;
        
        case EXT_TAG:
            if (d >= ne) {
                abort;
            }
            break;
        
        case LIST_TAG:
            // ~~~ Check for charlist cycle, 570 ~~~
            check_byte_range(d);
            while (d < current_character_being_worked_on) {
                qw = char_info(f, d);
                // N.B.: not |d|, since |char_base[f]| hasn't been adjusted yet
                if (char_tag(qw) != LIST_TAG) {
                    goto not_found;
                }
                d = rem_byte(qw); // next character on the list
            }
            if (d == current_character_being_worked_on) {
                abort; // yes, there's a cycle
            }
not_found:
            // ~~~ End section 570 ~~~
            break;
        
        default:
            do_nothing; // (|NO_TAG|)
        }
    }
    // ~~~ End section 569 ~~~
    // ~~~ Read box dimensions, 571 ~~~
    // ~~~ Replace |z| by |z'| and compute \alpha, \beta, 572 ~~~
    alpha = 16;
    while (z >= 0x800000) {
        z /= 2;
        alpha += alpha;
    }
    beta = 256 / alpha;
    alpha *= z;
    // ~~~ End section 572 ~~~
    for(k = width_base[f]; k <= lig_kern_base[f] - 1; k++) {
        store_scaled(font_info[k].sc);
    }
    if (font_info[width_base[f]].sc != 0) {
        abort; // width[0] must be zero
    }
    if (font_info[height_base[f]].sc != 0) {
        abort; // height[0] must be zero
    }
    if (font_info[depth_base[f]].sc != 0) {
        abort; // depth[0] must be zero
    }
    if (font_info[italic_base[f]].sc != 0) {
        abort; // italic[0] must be zero
    }
    // ~~~ End section 571 ~~~
    // ~~~ Read ligature/kern program, 573 ~~~
    bch_label = 0x7fff;
    bchar = 256;
    if (nl > 0) {
        for(k = lig_kern_base[f]; k <= kern_base[f] + KERN_BASE_OFFSET - 1; k++) {
            store_four_quarters(font_info[k]);
            if (a > 128) {
                if (256*c + d >= nl) {
                    abort;
                }
                if (a == 255 && k == lig_kern_base[f]) {
                    bchar = b;
                }
            }
            else {
                if (b != bchar) {
                    check_existence(b);
                }
                if (c < 128) {
                    check_existence(d); // check ligature
                }
                else if (256*(c - 128) + d >= nk) {
                    abort; // check kern
                }
                if (a < 128 && k - lig_kern_base[f] + a + 1 >= nl) {
                    abort;
                }
            }
        }
        if (a == 255) {
            bch_label = 256*c + d;
        }
    }
    for(k = kern_base[f] + KERN_BASE_OFFSET; k <= exten_base[f] - 1; k++) {
        store_scaled(font_info[k].sc);
    }
    // ~~~ End section 573 ~~~
    // ~~~ Read extensible character recipes, 574 ~~~
    for(k = exten_base[f]; k <= param_base[f] - 1; k++) {
        store_four_quarters(font_info[k]);
        if (a != 0) {
            check_existence(a);
        }
        if (b != 0) {
            check_existence(b);
        }
        if (c != 0) {
            check_existence(c);
        }
        check_existence(d);
    }
    // ~~~ End section 574 ~~~
    // ~~~ Read font parameters, 575 ~~~
    for(k = 1; k <= np; k++) {
        if (k == 1) {
            // the |slant| parameter is a pure number
            fget(sw);
            if (sw > 127) {
                sw -= 256;
            }
            fget(temp);
            sw = sw*256 + temp;
            fget(temp);
            sw = sw*256 + temp;
            fget(temp);
            font_info[param_base[f]].sc = sw*16 + temp/16;
        }
        else {
            store_scaled(font_info[param_base[f] + k - 1].sc);
        }
    }
    // if (eof(tmf_file)) then abort;
    for(k = np + 1; k <= 7; k++) {
        font_info[param_base[f] + k - 1].sc = 0;
    }
    // ~~~ End section 575 ~~~
    // ~~~ Make final adjustments and |goto done|, 576 ~~~
    if (np >= 7) {
        font_params[f] = np;
    }
    else {
        font_params[f] = 7;
    }
    hyphen_char[f] = default_hyphen_char;
    skew_char[f] = default_skew_char;
    if (bch_label < nl) {
        bchar_label[f] = bch_label + lig_kern_base[f];
    }
    else {
        bchar_label[f] = NON_ADDRESS;
    }
    font_bchar[f] = bchar;
    font_false_bchar[f] = bchar;
    if (bchar <= ec && bchar >= bc) {
        qw = char_info(f, bchar); // N.B.: not |qi(bchar)|
        if (char_exists(qw)) {
            font_false_bchar[f] = NON_CHAR;
        }
    }
    font_name[f] = nom;
    font_area[f] = aire;
    font_bc[f] = bc;
    font_ec[f] = ec;
    font_glue[f] = null;
    // adjust(char_base);
    // adjust(width_base);
    // adjust(lig_kern_base);
    // adjust(kern_base);
    // adjust(exten_base);
    decr(param_base[f]);
    fmem_ptr += lf;
    font_ptr = f;
    g = f;
    goto done;
    // ~~~ End section 576 ~~~
    // ~~~ End section 562 ~~~
bad_tfm:
    // ~~~ Report that the font won't be loaded, 561 ~~~
    start_font_error_message;
    if (file_opened) {
        print(" not loadable: Bad metric (TFM) file");
    }
    else {
        print(" not loadable: Metric (TFM) file not found");
    }
    help5("I wasn't able to read the size data for this font,")
        ("so I will ignore the font specification.")
        ("[Wizards can fix TFM files using TFtoPL/PLtoTF.]")
        ("You might try inserting a different font spec;")
        ("e.g., type `I\\font<same font id>=<substitute font name>'.");
    error();
    // ~~~ End section 561 ~~~
done:
    if (file_opened) {
        b_close(tfm_file);
    }
    return g;
}
// ~~~ End section 560 ~~~

// ~~~ Section 581 ~~~
void char_warning(internal_font_number f, eight_bits c) {
    if (tracing_lost_chars > 0) {
        begin_diagnostic();
        print_nl("Missing character: There is no ");
        print_strnumber(c);
        print(" in font ");
        slow_print(font_name[f]);
        print_char('!');
        end_diagnostic(false);
    }
}
// ~~~ End section 581 ~~~

// ~~~ Section 582 ~~~
pointer new_character(internal_font_number f, eight_bits c) {
    pointer p; // newly allocated node
    if (font_bc[f] <= c && font_ec[f] >= c && char_exists(char_info(f, c))) {
        p = get_avail();
        font(p) = f;
        character(p) = c;
        return p;
    }
    char_warning(f, c);
    return null;
}
// ~~~ End section 582 ~~~
