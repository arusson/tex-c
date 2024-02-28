// ~~~ Section 934 ~~~
// ~~~ Start file |hyph_scan.c|, 1382 ~~~
#ifdef INIT
#include "breaker.h"
#endif
#include "texerror.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// enters new exceptions
void new_hyph_exceptions() {
    int n;             // length of current word; not always a |small_number|
    int j;             // an index into |hc|
    int h;             // an index into |hyph_word| and |hyph_list|
    str_number k;      // an index into |str_start|
    pointer p;         // head of a list of hyphen positions
    pointer q;         // used when creating a new node for list |p|
    str_number s, t;   // strings being compared or stored
    pool_pointer u, v; // indices into |str_pool|
    
    scan_left_brace(); // a left brace must follow \\hyphenation}
    set_cur_lang;
    // ~~~ Enter as many hyphenation exceptions as are listed, until coming to a right brace; then |return|, 935 ~~~
    n = 0;
    p = null;
    while(true) {
        get_x_token();
reswitch:
        switch (cur_cmd) {
        case LETTER:
        case OTHER_CHAR:
        case CHAR_GIVEN:
            // ~~~ Append a new letter or hyphen, 937 ~~~
            if (cur_chr == '-') {
                // ~~~ Append the value |n| to list |p|, 938 ~~~
                if (n < 63) {
                    q = get_avail();
                    link(q) = p;
                    info(q) = n;
                    p = q;
                }
                // ~~~ End section 938 ~~~
            }
            else {
                if (lc_code(cur_chr) == 0) {
                    print_err("Not a letter");
                    help2("Letters in \\hyphenation words must have \\lccode>0.")
                        ("Proceed; I'll ignore the character I just read.");
                    error();
                }
                else if (n < 63) {
                    incr(n);
                    hc[n] = lc_code(cur_chr);
                }
            }
            // ~~~ End section 937 ~~~
            break;
        
        case CHAR_NUM:
            scan_char_num();
            cur_chr = cur_val;
            cur_cmd = CHAR_GIVEN;
            goto reswitch;
        
        case SPACER:
        case RIGHT_BRACE:
            if (n > 1) {
                // ~~~ Enter a hyphenation exception, 939 ~~~
                incr(n);
                hc[n] = cur_lang;
                str_room(n);
                h = 0;
                for(j = 1; j <= n; j++) {
                    h = (h + h + hc[j]) % HYPH_SIZE;
                    append_char(hc[j]);
                }
                s = make_string();
                // ~~~ Insert the pair |(s,p)| into the exception table, 940 ~~~
                if (hyph_count == HYPH_SIZE) {
                    overflow("exception dictionary", HYPH_SIZE);
                }
                incr(hyph_count);
                while (hyph_word[h] != 0) {
                    // ~~~ If the string |hyph_word[h]| is less than or equal to |s|, interchange |(hyph_word[h],hyph_list[h])| with |(s,p)|, 941 ~~~
                    k = hyph_word[h];
                    if (length(k) < length(s)) {
                        goto found;
                    }
                    if (length(k) > length(s)) {
                        goto not_found;
                    }
                    u = str_start[k];
                    v = str_start[s];
                    do {
                        if (str_pool[u] < str_pool[v]) {
                            goto found;
                        }
                        if (str_pool[u] > str_pool[v]) {
                            goto not_found;
                        }
                        incr(u);
                        incr(v);
                    } while (u != str_start[k + 1]);
found:
                    q = hyph_list[h];
                    hyph_list[h] = p;
                    p = q;
                    t = hyph_word[h];
                    hyph_word[h] = s;
                    s = t;
not_found:
                    // ~~~ End section 941 ~~~
                    if (h > 0) {
                        decr(h);
                    }
                    else {
                        h = HYPH_SIZE;
                    }
                }
                hyph_word[h] = s;
                hyph_list[h] = p;
                // ~~~ End section 940 ~~~
                // ~~~ End section 939 ~~~
            }
            if (cur_cmd == RIGHT_BRACE) {
                return;
            }
            n = 0;
            p = null;
            break;
        
        default:
            // ~~~ Give improper \hyphenation error, 936 ~~~
            print_err("Improper ");
            print_esc("hyphenation");
            print(" will be flushed");
            help2("Hyphenation exceptions must contain only letters")
                ("and hyphens. But continue; I'll forgive and forget.");
            error();
            // ~~~ End section 936 ~~~
        }
    }
    // ~~~ End section 935 ~~~
}
// ~~~ End section 934 ~~~

// ~~~ Section 942 ~~~
#ifdef INIT
// ~~~ Declare procedures for preprocessing hyphenation patterns, 944 ~~~
quarterword new_trie_op(small_number d, small_number n, quarterword v) {
    int h;         // trial hash location
    quarterword u; // trial op code
    int l;         // pointer to stored data
    h = abs(n + 313*d + 361*v + 1009*cur_lang) % (TRIE_OP_SIZE + TRIE_OP_SIZE) - TRIE_OP_SIZE;
    while(true) {
        l = trie_op_hash[h];
        if (l == 0) {
            // empty position found for a new op
            if (trie_op_ptr == TRIE_OP_SIZE) {
                overflow("pattern memory ops", TRIE_OP_SIZE);
            }
            u = trie_used[cur_lang];
            if (u == MAX_QUARTERWORD) {
                overflow("pattern memory ops per language", MAX_QUARTERWORD - MIN_QUARTERWORD);
            }
            incr(trie_op_ptr);
            incr(u);
            trie_used[cur_lang] = u;
            hyf_distance[trie_op_ptr] = d;
            hyf_num[trie_op_ptr] = n;
            hyf_next[trie_op_ptr] = v;
            trie_op_lang[trie_op_ptr] = cur_lang;
            trie_op_hash[h] = trie_op_ptr;
            trie_op_val[trie_op_ptr] = u;
            return u;
        }
        if (hyf_distance[l] == d
            && hyf_num[l] == n
            && hyf_next[l] == v
            && trie_op_lang[l] == cur_lang)
        {
            return trie_op_val[l];
        }
        if (h > -TRIE_OP_SIZE) {
            decr(h);
        }
        else {
            h = TRIE_OP_SIZE;
        }
    }
}

// ~~~ Section 948 ~~~
// converts to a canonical form
int trie_node(trie_pointer p) {
    int h; // trial hash location
    int q; // trial trie node
    h = abs(trie_c[p] + 1009*trie_o[p] + 2718*trie_l[p] + 3142*trie_r[p]) % TRIE_SIZE;
    while(true) {
        q = trie_hash[h];
        if (q == 0) {
            trie_hash[h] = p;
            return p;
        }
        if (trie_c[q] == trie_c[p]
            && trie_o[q] == trie_o[p]
            && trie_l[q] == trie_l[p]
            && trie_r[q] == trie_r[p])
        {
            return q;
        }
        if (h > 0) {
            decr(h);
        }
        else {
            h = TRIE_SIZE;
        }
    }
}
// ~~~ End section 948 ~~~

// ~~~ Section 949 ~~~
int compress_trie(trie_pointer p) {
    if (p == 0) {
        return 0;
    }
    else {
        trie_l[p] = compress_trie(trie_l[p]);
        trie_r[p] = compress_trie(trie_r[p]);
        return trie_node(p);
    }
}
// ~~~ End section 949 ~~~

// ~~~ Section 953 ~~~
// packs a family into |trie|
void first_fit(trie_pointer p) {
    int h;        // candidate for |trie_ref[p]|
    int z;        // runs through holes
    int q;        // runs through the family starting at |p|
    ASCII_code c; // smallest character in the family
    int l, r;     // left and right neighbors
    int ll;       // upper limit of |trie_min| updating
    c = trie_c[p];
    z = trie_min[c]; // get the first conceivably good hole
    while(true) {
        h = z - c;
        // ~~~ Ensure that |trie_max >= h + 256|, 954 ~~~
        if (trie_max < h + 256) {
            if (TRIE_SIZE <= h + 256) {
                overflow("pattern memory", TRIE_SIZE);
            }
            do {
                incr(trie_max);
                trie_taken[trie_max] = false;
                trie_link(trie_max) = trie_max + 1;
                trie_back(trie_max) = trie_max - 1;
            } while (trie_max != h + 256);
        }
        // ~~~ End section 954 ~~~
        if (trie_taken[h]) {
            goto not_found;
        }
        // ~~~ If all characters of the family fit relative to |h|, then |goto found|, otherwise |goto not_found|, 955 ~~~
        q = trie_r[p];
        while (q > 0) {
            if (trie_link(h + trie_c[q]) == 0) {
                goto not_found;
            }
            q = trie_r[q];
        }
        goto found;
        // ~~~ End section 955 ~~~
not_found:
        z = trie_link(z); // move to the next hole
    }
found:
    // ~~~ Pack the family into |trie| relative to |h|, 956 ~~~
    trie_taken[h] = true;
    trie_ref[p] = h;
    q = p;
    do {
        z = h + trie_c[q];
        l = trie_back(z);
        r = trie_link(z);
        trie_back(r) = l;
        trie_link(l) = r;
        trie_link(z) = 0;
        if (l < 256) {
            if (z < 256) {
                ll = z;
            }
            else {
                ll = 256;
            }
            do {
                trie_min[l] = r;
                incr(l);
            } while (l != ll);
        }
        q = trie_r[q];
    } while (q != 0);
    // ~~~ End section 956 ~~~
}
// ~~~ End section 953 ~~~

// ~~~ Section 957 ~~~
// pack subtries of a family
void trie_pack(trie_pointer p) {
    int q; // a local variable that need not be saved on recursive calls
    do {
        q = trie_l[p];
        if (q > 0 && trie_ref[q] == 0) {
            first_fit(q);
            trie_pack(q);
        }
        p = trie_r[p];
    } while (p != 0);
}
// ~~~ End section 957 ~~~

// ~~~ Section 959 ~~~
// moves |p| and its siblings into |trie|
void trie_fix(trie_pointer p) {
    int q;        // a local variable that need not be saved on recursive calls
    ASCII_code c; // another one that need not be saved
    int z;        // |trie| reference; this local variable must be saved
    z = trie_ref[p];
    do {
        q = trie_l[p];
        c = trie_c[p];
        trie_link(z + c) = trie_ref[q];
        trie_char(z + c) = c;
        trie_op(z + c) = trie_o[p];
        if (q > 0) {
            trie_fix(q);
        }
        p = trie_r[p];
    } while (p != 0);
}
// ~~~ End section 959 ~~~

// ~~~ Section 960 ~~~
// initializes the hyphenation pattern data
void new_patterns() {
    int k, l;          // indices into |hc| and |hyf|; not always in |small_number| range
    bool digit_sensed; // should the next digit be treated as a letter?
    quarterword v;     // trie op code
    int p, q;          // nodes of trie traversed during insertion
    bool first_child;  // is |p == trie_l[q]|?
    ASCII_code c;      // character being inserted
    
    if (trie_not_ready) {
        set_cur_lang;
        scan_left_brace(); // a left brace must follow \patterns
        // ~~~ Enter all of the patterns into a linked trie, until coming to a right brace, 961 ~~~
        k = 0;
        hyf[0] = 0;
        digit_sensed = false;
        while(true) {
            get_x_token();
            switch (cur_cmd) {
            case LETTER:
            case OTHER_CHAR:
                // ~~~ Append a new letter or a hyphen level, 962 ~~~
                if (digit_sensed || cur_chr < '0' || cur_chr > '9') {
                    if (cur_chr == '.') {
                        cur_chr = 0; // edge-of-word delimiter
                    }
                    else {
                        cur_chr = lc_code(cur_chr);
                        if (cur_chr == 0) {
                            print_err("Nonletter");
                            help1("(See Appendix H.)");
                            error();
                        }
                    }
                    if (k < 63) {
                        incr(k);
                        hc[k] = cur_chr;
                        hyf[k] = 0;
                        digit_sensed = false;
                    }
                }
                else if (k < 63) {
                    hyf[k] = cur_chr - '0';
                    digit_sensed = true;
                }
                // ~~~ End section 962 ~~~
                break;
            
            case SPACER:
            case RIGHT_BRACE:
                if (k > 0) {
                    // ~~~ Insert a new pattern into the linked trie, 963 ~~~
                    // ~~~ Compute the trie op code, |v|, and set |l = 0|, 965 ~~~
                    if (hc[1] == 0) {
                        hyf[0] = 0;
                    }
                    if (hc[k] == 0) {
                        hyf[k] = 0;
                    }
                    l = k;
                    v = MIN_QUARTERWORD;
                    while(true) {
                        if (hyf[l] != 0) {
                            v = new_trie_op(k - l, hyf[l], v);
                        }
                        if (l > 0) {
                            decr(l);
                        }
                        else {
                            break; // goto done1
                        }
                    }
                    // done1:
                    // ~~~ End section 965 ~~~
                    q = 0;
                    hc[0] = cur_lang;
                    while (l <= k) {
                        c = hc[l];
                        incr(l);
                        p = trie_l[q];
                        first_child = true;
                        while (p > 0 && c > trie_c[p]) {
                            q = p;
                            p = trie_r[q];
                            first_child = false;
                        }
                        if (p == 0 || c < trie_c[p]) {
                            // ~~~ Insert a new trie node between |q| and |p|, and make |p| point to it, 964 ~~~
                            if (trie_ptr == TRIE_SIZE) {
                                overflow("pattern memory", TRIE_SIZE);
                            }
                            incr(trie_ptr);
                            trie_r[trie_ptr] = p;
                            p = trie_ptr;
                            trie_l[p] = 0;
                            if (first_child) {
                                trie_l[q] = p;
                            }
                            else {
                                trie_r[q] = p;
                            }
                            trie_c[p] = c;
                            trie_o[p] = MIN_QUARTERWORD;
                            // ~~~ End section 964 ~~~
                        }
                        q = p; // now node |q| represents $p_1\ldots p_{l - 1}$
                    }
                    if (trie_o[q] != MIN_QUARTERWORD) {
                        print_err("Duplicate pattern");
                        help1("(See Appendix H.)");
                        error();
                    }
                    trie_o[q] = v;
                    // ~~~ End section 963 ~~~
                }
                if (cur_cmd == RIGHT_BRACE) {
                    goto done;
                }
                k = 0;
                hyf[0] = 0;
                digit_sensed = false;
                break;
          
            default:
                print_err("Bad ");
                print_esc("patterns");
                help1("(See Appendix H.)");
                error();
            }
        }
done:
        // ~~~ End section 961 ~~~
    }
    else {
        print_err("Too late for ");
        print_esc("patterns");
        help1("All patterns must be given before typesetting begins.");
        error();
        link(GARBAGE) = scan_toks(false, false);
        flush_list(def_ref);
    }
}
// ~~~ End section 960 ~~~

// ~~~ Section 966 ~~~
void init_trie() {
    int p;         // pointer for initialization
    int j, k, t;   // all-purpose registers for initialization
    int r, s;      // used to clean up the packed |trie|
    memory_word h; // template used to zero out |trie|'s holes
    
    // ~~~ Get ready to compress the trie, 952 ~~~
    // ~~~ Sort the hyphenation op tables into proper order, 945 ~~~
    op_start[0] = -MIN_QUARTERWORD;
    for(j = 1; j <= 255; j++) {
        op_start[j] = op_start[j - 1] + trie_used[j - 1];
    }
    for(j = 1; j <= trie_op_ptr; j++) {
        // destination
        trie_op_hash[j] = op_start[trie_op_lang[j]] + trie_op_val[j];
    }
    for(j = 1; j <= trie_op_ptr; j++) {
        while (trie_op_hash[j] > j) {
            k = trie_op_hash[j];
            t = hyf_distance[k];
            hyf_distance[k] = hyf_distance[j];
            hyf_distance[j] = t;
            t = hyf_num[k];
            hyf_num[k] = hyf_num[j];
            hyf_num[j] = t;
            t = hyf_next[k];
            hyf_next[k] = hyf_next[j];
            hyf_next[j] = t;
            trie_op_hash[j] = trie_op_hash[k];
            trie_op_hash[k] = k;
        }
    }
    // ~~~ End section 945 ~~~
    for(p = 0; p <= TRIE_SIZE; p++) {
        trie_hash[p] = 0;
    }
    trie_root = compress_trie(trie_root); // identify equivalent subtries
    for(p = 0; p <= trie_ptr; p++) {
        trie_ref[p] = 0;
    }
    for(p = 0; p <= 255; p++) {
        trie_min[p] = p + 1;
    }
    trie_link(0) = 1;
    trie_max = 0;
    // ~~~ End section 952 ~~~
    if (trie_root != 0) {
        first_fit(trie_root);
        trie_pack(trie_root);
    }
    // ~~~ Move the data into |trie|, 958 ~~~
    hh_rh(h) = 0;
    hh_b0(h) = MIN_QUARTERWORD;
    hh_b1(h) = MIN_QUARTERWORD; // |trie_link = 0|, |trie_op = MIN_QUARTERWORD|, |trie_char = 0|
    if (trie_root == 0) {
        // no patterns were given
        for(r = 0; r <= 256; r++) {
            trie[r] = h;
        }
        trie_max = 256;
    }
    else {
        trie_fix(trie_root); // this fixes the non-holes in |trie|
        r = 0; // now we will zero out all the holes
        do {
            s = trie_link(r);
            trie[r] = h;
            r = s;
        } while (r <= trie_max);
    }
    trie_char(0) = '?'; // make |trie_char(c) != c| for all |c|
    // ~~~ End section 958 ~~~
    trie_not_ready = false;
}
// ~~~ End section 966 ~~~
// ~~~ End section 944 ~~~
#endif
// ~~~ End section 942 ~~~
