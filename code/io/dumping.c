// ~~~ Section 523 ~~~
// ~~~ Start file |dumping.c|, 1382 ~~~
#ifdef INIT
#include "texerror.h"
#include "breaker.h"
#else
#include "io.h"
#endif
#include "parser.h"
// ~~~ End section 1382 ~~~

void pack_buffered_name(small_number n, int a, int b) {
    int k; // number of positions filled in |name_of_file|
    ASCII_code c; // character being packed
    int j; // index into |buffer| or |tex_format_default|
    if (n + b - a + 1 + FORMAT_EXT_LENGTH > FILE_NAME_SIZE) {
        b = a + FILE_NAME_SIZE - n - 1 - FORMAT_EXT_LENGTH;
    }
    k = 0;
    for(j = 0; j < n; j++) {
        append_to_name(XORD[(int)tex_format_default[j]]);
    }
    for(j = a; j <= b; j++) {
        append_to_name(buffer[j]);
    }
    for(j = FORMAT_DEFAULT_LENGTH - FORMAT_EXT_LENGTH; j < FORMAT_DEFAULT_LENGTH; j++) {
        append_to_name(XORD[(int)tex_format_default[j]]);
    }
    if (k <= FILE_NAME_SIZE) {
        name_length = k;
    }
    else {
        name_length = FILE_NAME_SIZE;
    }
    append_to_name_nul;
}
// ~~~ End section 523 ~~~

// ~~~ Section 524 ~~~
bool open_fmt_file() {
    int j; // the first space after the format file name
    j = loc;
    if (buffer[loc] == '&') {
        incr(loc);
        j = loc;
        buffer[last] = ' ';
        while (buffer[j] != ' ') {
            incr(j);
        }
        pack_buffered_name(0, loc, j - 1); // try first without the system file area
        if (w_open_in(&fmt_file)) {
            goto found;
        }
        pack_buffered_name(FORMAT_AREA_LENGTH, loc, j - 1); // now try the system format file area
        if (w_open_in(&fmt_file)) {
            goto found;
        }
        wterm_ln("Sorry, I can't find that format; will try PLAIN.");
        update_terminal;
    }
    // now pull out all the stops: try for the system plain file
    pack_buffered_name(FORMAT_DEFAULT_LENGTH - FORMAT_EXT_LENGTH, 1, 0);
    if (!w_open_in(&fmt_file)) {
        wterm_ln("I can't find the PLAIN format file!");
        return false;
    }
found:
    loc = j;
    return true;
}
// ~~~ End section 524 ~~~

// ~~~ Section 1302 ~~~
#ifdef INIT
void store_fmt_file() {
    int j, k, l;   // all-purpose indices
    pointer p, q;  // all-purpose pointers
    int x;         // something to dump
    memory_word w; // four ASCII codes
    // ~~~ If dumping is not allowed, abort, 1304 ~~~
    if (save_ptr != 0) {
        print_err("You can't dump inside a group");
        help1("`{...\\dump}' is a no-no.");
        succumb();
    }
    // ~~~ End section 1304 ~~~
    // ~~~ Create the |format_ident|, open the format file, and inform the user that dumping has begun, 1328 ~~~
    selector = NEW_STRING;
    print(" (preloaded format=");
    print_strnumber(job_name);
    print_char(' ');
    print_int(year);
    print_char('.');
    print_int(month);
    print_char('.');
    print_int(day);
    print_char(')');
    if (interaction == BATCH_MODE) {
        selector = LOG_ONLY;
    }
    else {
        selector = TERM_AND_LOG;
    }
    str_room(1);
    format_ident = make_string();
    pack_job_name(FORMAT_EXTENSION);
    while (!w_open_out(&fmt_file)) {
        prompt_file_name("format file name", FORMAT_EXTENSION);
    }
    print_nl("Beginning to dump on file ");
    slow_print(make_name_string());
    flush_string;
    print_nl("");
    slow_print(format_ident);
    // ~~~ End section 1328 ~~~
    // ~~~ Dump constants for consistency check, 1307 ~~~
    dump_int(0);
    dump_int(MEM_BOT);
    dump_int(MEM_TOP);
    dump_int(EQTB_SIZE);
    dump_int(HASH_PRIME);
    dump_int(HYPH_SIZE);
    // ~~~ End section 1307 ~~~
    // ~~~ Dump the string pool, 1309 ~~~
    dump_int(pool_ptr);
    dump_int(str_ptr);
    for(k = 0; k <= str_ptr; k++) {
        dump_int(str_start[k]);
    }
    k = 0;
    while (k + 4 < pool_ptr) {
        dump_four_ASCII;
        k += 4;
    }
    k = pool_ptr - 4;
    dump_four_ASCII;
    print_ln();
    print_int(str_ptr);
    print(" strings of total length ");
    print_int(pool_ptr);
    // ~~~ End section 1309 ~~~
    // ~~~ Dump the dynamic memory, 1311 ~~~
    sort_avail();
    var_used = 0;
    dump_int(lo_mem_max);
    dump_int(rover);
    p = MEM_BOT;
    q = rover;
    x = 0;
    do {
        for(k = p; k <= q + 1; k++) {
            dump_wd(mem[k]);
        }
        x =+ q + 2 - p;
        var_used += q - p;
        p = q + node_size(q);
        q = rlink(q);
    } while (q != rover);
    var_used += lo_mem_max - p;
    dyn_used = mem_end + 1 - hi_mem_min;
    for(k = p; k <= lo_mem_max; k++) {
        dump_wd(mem[k]);
    }
    x += lo_mem_max + 1 - p;
    dump_int(hi_mem_min);
    dump_int(avail);
    for(k = hi_mem_min; k <= mem_end; k++) {
        dump_wd(mem[k]);
    }
    x += mem_end + 1 - hi_mem_min;
    p = avail;
    while (p != null) {
        decr(dyn_used);
        p = link(p);
    }
    dump_int(var_used);
    dump_int(dyn_used);
    print_ln();
    print_int(x);
    print(" memory locations dumped; current usage is ");
    print_int(var_used);
    print_char('&');
    print_int(dyn_used);
    // ~~~ End section 1311 ~~~
    // ~~~ Dump the table of equivalents, 1313 ~~~
    // ~~~ Dump regions 1 to 4 of |eqtb|, 1315 ~~~
    k = ACTIVE_BASE;
    do {
        j = k;
        while (j < INT_BASE - 1) {
            if (equiv(j) == equiv(j + 1)
                && eq_type(j) == eq_type(j + 1)
                && eq_level(j) == eq_level(j + 1))
            {
                goto found1;
            }
            incr(j);
        }
        l = INT_BASE;
        goto done1; // |j = INT_BASE - 1|
found1:
        incr(j);
        l = j;
        while (j < INT_BASE - 1) {
            if (equiv(j) != equiv(j + 1)
                || eq_type(j) != eq_type(j + 1)
                || eq_level(j) != eq_level(j + 1))
            {
                goto done1;
            }
            incr(j);
        }
done1:
        dump_int(l - k);
        while (k < l) {
            dump_wd(eqtb[k]);
            incr(k);
        }
        k = j + 1;
        dump_int(k - l);
    } while (k != INT_BASE);
    // ~~~ End section 1315 ~~~
    // ~~~ Dump regions 5 and 6 of |eqtb|, 1316 ~~~
    do {
        j = k;
        while (j < EQTB_SIZE) {
            if (eqtb[j].integer == eqtb[j + 1].integer) {
                goto found2;
            }
            incr(j);
        }
        l = EQTB_SIZE + 1;
        goto done2; // |j = EQTB_SIZE|
found2:
        incr(j);
        l = j;
        while (j < EQTB_SIZE) {
            if (eqtb[j].integer != eqtb[j + 1].integer) {
                goto done2;
            }
            incr(j);
        }
done2:
        dump_int(l - k);
        while (k < l) {
            dump_wd(eqtb[k]);
            incr(k);
        }
        k = j + 1;
        dump_int(k - l);
    } while (k <= EQTB_SIZE);
    // ~~~ End section 1316 ~~~
    dump_int(par_loc);
    dump_int(write_loc);
    // ~~~ Dump the hash table, 1318 ~~~
    dump_int(hash_used);
    cs_count = FROZEN_CONTROL_SEQUENCE - 1 - hash_used;
    for(p = HASH_BASE; p <= hash_used; p++) {
        if (text(p) != 0) {
            dump_int(p);
            dump_hh(hash[p]);
            incr(cs_count);
        }
    }
    for(p = hash_used + 1; p <= UNDEFINED_CONTROL_SEQUENCE - 1; p++) {
        dump_hh(hash[p]);
    }
    dump_int(cs_count);
    print_ln();
    print_int(cs_count);
    print(" multiletter control sequences");
    // ~~~ End section 1318 ~~~
    // ~~~ End section 1313 ~~~
    // ~~~ Dump the font information, 1320 ~~~
    dump_int(fmem_ptr);
    for(k = 0; k <= fmem_ptr - 1; k++) {
        dump_wd(font_info[k]);
    }
    dump_int(font_ptr);
    for(k = NULL_FONT; k <= font_ptr; k++) {
        // ~~~ Dump the array info for internal font number |k|, 1322 ~~~
        dump_qqqq(font_check[k]);
        dump_int(font_size[k]);
        dump_int(font_dsize[k]);
        dump_int(font_params[k]);
        dump_int(hyphen_char[k]);
        dump_int(skew_char[k]);
        dump_int(font_name[k]);
        dump_int(font_area[k]);
        dump_int(font_bc[k]);
        dump_int(font_ec[k]);
        dump_int(char_base[k]);
        dump_int(width_base[k]);
        dump_int(height_base[k]);
        dump_int(depth_base[k]);
        dump_int(italic_base[k]);
        dump_int(lig_kern_base[k]);
        dump_int(kern_base[k]);
        dump_int(exten_base[k]);
        dump_int(param_base[k]);
        dump_int(font_glue[k]);
        dump_int(bchar_label[k]);
        dump_int(font_bchar[k]);
        dump_int(font_false_bchar[k]);
        print_nl("\\font");
        print_esc_strnumber(font_id_text(k));
        print_char('=');
        print_file_name(font_name[k], font_area[k], EMPTY_STRING);
        if (font_size[k] != font_dsize[k]) {
            print(" at ");
            print_scaled(font_size[k]);
            print("pt");
        }
        // ~~~ End section 1322 ~~~
    }
    print_ln();
    print_int(fmem_ptr - 7);
    print(" words of font info for ");
    print_int(font_ptr - FONT_BASE);
    print(" preloaded font");
    if (font_ptr != FONT_BASE + 1) {
        print_char('s');
    }
    // ~~~ End section 1320 ~~~
    // ~~~ Dump the hyphenation tables, 1324 ~~~
    dump_int(hyph_count);
    for(k = 0; k <= HYPH_SIZE; k++) {
        if (hyph_word[k] != 0) {
            dump_int(k);
            dump_int(hyph_word[k]);
            dump_int(hyph_list[k]);
        }
    }
    print_ln();
    print_int(hyph_count);
    print(" hyphenation exception");
    if (hyph_count != 1) {
        print_char('s');
    }
    if (trie_not_ready) {
        init_trie();
    }
    dump_int(trie_max);
    for(k = 0; k <= trie_max; k++) {
        dump_hh(trie[k]);
    }
    dump_int(trie_op_ptr);
    for(k = 1; k <= trie_op_ptr; k++) {
        dump_int(hyf_distance[k]);
        dump_int(hyf_num[k]);
        dump_int(hyf_next[k]);
    }
    print_nl("Hyphenation trie of length ");
    print_int(trie_max);
    print(" has ");
    print_int(trie_op_ptr);
    print(" op");
    if (trie_op_ptr != 1) {
        print_char('s');
    }
    print(" out of ");
    print_int(TRIE_OP_SIZE);
    for(k = 255; k>= 0; k--) {
        if (trie_used[k] > MIN_QUARTERWORD) {
            print_nl("  ");
            print_int(trie_used[k]);
            print(" for language ");
            print_int(k);
            dump_int(k);
            dump_int(trie_used[k]);
        }
    }
    // ~~~ End section 1324 ~~~
    // ~~~ Dump a couple more things and the closing check word, 1326 ~~~
    dump_int(interaction);
    dump_int(format_ident);
    dump_int(69069);
    tracing_stats = 0;
    // ~~~ End section 1326 ~~~
    // ~~~ Close the format file, 1329 ~~~
    w_close(fmt_file);
    // ~~~ End section 1329 ~~~
}
#endif
// ~~~ End section 1302 ~~~

// ~~~ Section 1303 ~~~
bool load_fmt_file() {
    int j, k;      // all-purpose indices
    pointer p, q;  // all-purpose pointers
    int x;         // something undumped
    memory_word w; // four ASCII codes
    // ~~~ Undump constants for consistency check, 1308 ~~~
    undump_int(x);
    if (x != 0) {
        goto bad_fmt; // check that strings are the same
    }
    undump_int(x);
    if (x != MEM_BOT) {
        goto bad_fmt;
    }
    undump_int(x);
    if (x != MEM_TOP) {
        goto bad_fmt;
    }
    undump_int(x);
    if (x != EQTB_SIZE) {
        goto bad_fmt;
    }
    undump_int(x);
    if (x != HASH_PRIME) {
        goto bad_fmt;
    }
    undump_int(x);
    if (x != HYPH_SIZE) {
        goto bad_fmt;
    }
    // ~~~ End section 1308 ~~~
    // ~~~ Undump the string pool, 1310 ~~~
    undump_size(0, POOL_SIZE, "string pool size", pool_ptr);
    undump_size(0, MAX_STRINGS, "max strings", str_ptr);
    for(k = 0; k <= str_ptr; k++) {
        undump(0, pool_ptr, str_start[k]);
    }
    k = 0;
    while (k + 4 < pool_ptr) {
        undump_four_ASCII;
        k += 4;
    }
    k = pool_ptr - 4;
    undump_four_ASCII;
    init_str_ptr = str_ptr;
    init_pool_ptr = pool_ptr;
    // ~~~ End section 1310 ~~~
    // ~~~ Undump the dynamic memory, 1312 ~~~
    undump(LO_MEM_STAT_MAX + 1000, HI_MEM_STAT_MIN - 1, lo_mem_max);
    undump(LO_MEM_STAT_MAX + 1, lo_mem_max, rover);
    p = MEM_BOT;
    q = rover;
    do {
        for(k = p; k <= q + 1; k++) {
            undump_wd(mem[k]);
        }
        p = q + node_size(q);
        if (p > lo_mem_max ||
            (q >= rlink(q) && rlink(q) != rover))
        {
            goto bad_fmt;
        }
        q = rlink(q);
    } while (q != rover);
    for(k = p; k <= lo_mem_max; k++) {
        undump_wd(mem[k]);
    }
    /* This condition is never true in this implementation
    if (MEM_MIN < MEM_BOT - 2) {
        // make more low memory available
        p = llink(rover);
        q = MEM_MIN + 1;
        link(MEM_MIN) = null;
        info(MEM_MIN) = null; // we don't use the bottom word
        rlink(p) = q;
        llink(rover) = q;
        rlink(q) = rover;
        llink(q) = p;
        link(q) = EMPTY_FLAG;
        node_size(q) = MEM_BOT - q;
    } */
    undump(lo_mem_max + 1, HI_MEM_STAT_MIN, hi_mem_min);
    undump(null, MEM_TOP, avail);
    mem_end = MEM_TOP;
    for(k = hi_mem_min; k <= mem_end; k++) {
        undump_wd(mem[k]);
    }
    undump_int(var_used);
    undump_int(dyn_used);
    // ~~~ End section 1312 ~~~
    // ~~~ Undump the table of equivalents, 1314 ~~~
    // ~~~ Undump regions 1 to 6 of |eqtb|, 1317 ~~~
    k = ACTIVE_BASE;
    do {
        undump_int(x);
        if (x < 1 || k + x > EQTB_SIZE + 1) {
            goto bad_fmt;
        }
        for(j = k; j <= k + x - 1; j++) {
            undump_wd(eqtb[j]);
        }
        k += x;
    undump_int(x);
    if (x < 0 || k + x > EQTB_SIZE + 1) {
        goto bad_fmt;
    }
    for(j = k; j <= k + x - 1; j++) {
        eqtb[j] = eqtb[k - 1];
    }
    k += x;
    } while (k <= EQTB_SIZE);
    // ~~~ End section 1317 ~~~
    undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, par_loc);
    par_token = CS_TOKEN_FLAG + par_loc;
    undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, write_loc);
    // ~~~ Undump the hash table, 1319 ~~~
    undump(HASH_BASE, FROZEN_CONTROL_SEQUENCE, hash_used);
    p = HASH_BASE - 1;
    do {
        undump(p + 1, hash_used, p);
        undump_hh(hash[p]);
    } while (p != hash_used);
    for(p = hash_used + 1; p <= UNDEFINED_CONTROL_SEQUENCE - 1; p++) {
        undump_hh(hash[p]);
    }
    undump_int(cs_count);
    // ~~~ End section 1319 ~~~
    // ~~~ End section 1314 ~~~
    // ~~~ Undump the font information, 1321 ~~~
    undump_size(7, FONT_MEM_SIZE, "font mem size", fmem_ptr);
    for(k = 0; k <= fmem_ptr - 1; k++) {
        undump_wd(font_info[k]);
    }
    undump_size(FONT_BASE, FONT_MAX, "font max", font_ptr);
    for(k = NULL_FONT; k <= font_ptr; k++) {
        // ~~~ Undump the array info for internal font number |k|, 1323 ~~~
        undump_qqqq(font_check[k]);
        undump_int(font_size[k]);
        undump_int(font_dsize[k]);
        undump(MIN_HALFWORD, MAX_HALFWORD, font_params[k]);
        undump_int(hyphen_char[k]);
        undump_int(skew_char[k]);
        undump(0, str_ptr, font_name[k]);
        undump(0, str_ptr, font_area[k]);
        undump(0, 255, font_bc[k]);
        undump(0, 255, font_ec[k]);
        undump_int(char_base[k]);
        undump_int(width_base[k]);
        undump_int(height_base[k]);
        undump_int(depth_base[k]);
        undump_int(italic_base[k]);
        undump_int(lig_kern_base[k]);
        undump_int(kern_base[k]);
        undump_int(exten_base[k]);
        undump_int(param_base[k]);
        undump(MIN_HALFWORD, lo_mem_max, font_glue[k]);
        undump(0, fmem_ptr - 1, bchar_label[k]);
        undump(MIN_QUARTERWORD, NON_CHAR, font_bchar[k]);
        undump(MIN_QUARTERWORD, NON_CHAR, font_false_bchar[k]);
        // ~~~ End section 1323 ~~~
    }
    // ~~~ End section 1321 ~~~
    // ~~~ Undump the hyphenation tables, 1325 ~~~
    undump(0, HYPH_SIZE, hyph_count);
    for(k = 1; k <= hyph_count; k++) {
        undump(0, HYPH_SIZE, j);
        undump(0, str_ptr, hyph_word[j]);
        undump(MIN_HALFWORD, MAX_HALFWORD, hyph_list[j]);
    }
    undump_size(0, TRIE_SIZE, "trie size", j);
    
#ifdef INIT
    trie_max = j;
#endif
    
    for(k = 0; k <= j; k++) {
        undump_hh(trie[k]);
    }
    undump_size(0, TRIE_OP_SIZE, "trie op size", j);
    
#ifdef INIT
    trie_op_ptr = j;
#endif
    
    for(k = 1; k <= j; k++) {
        undump(0, 63, hyf_distance[k]); // a |small_number|
        undump(0, 63, hyf_num[k]);
        undump(MIN_QUARTERWORD, MAX_QUARTERWORD, hyf_next[k]);
    }
    
#ifdef INIT
    for(k = 0; k <= 255; k++) {
        trie_used[k] = MIN_QUARTERWORD;
    }
#endif
    
    k = 256;
    while (j > 0) {
        undump(0, k - 1, k);
        undump(1, j, x);
    
#ifdef INIT
        trie_used[k] = x;
#endif
    
        j -= x;
        op_start[k] = j;
    }
    
#ifdef INIT
    trie_not_ready = false;
#endif
    // ~~~ End section 1325 ~~~
    // ~~~ Undump a couple more things and the closing check word, 1327 ~~~
    undump(BATCH_MODE, ERROR_STOP_MODE, interaction);
    undump(0, str_ptr, format_ident);
    undump_int(x);
    if (x != 69069) {
        goto bad_fmt;
    }
    // ~~~ End section 1327 ~~~
    return true; // it worked!
bad_fmt:
    wterm_ln("(Fatal format file error; I'm stymied)");
    return false;
}
// ~~~ End section 1303 ~~~
