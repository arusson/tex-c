# Section 565

```c << Read the TFM size fields >>=
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
```
