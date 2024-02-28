# Section 261

The value of *HASH_PRIME* should be roughly 85% of *HASH_SIZE*, and it should be a prime number.
The theory of hashing tells us to expect fewer than two table probes, on the average, when the search is successful.
[See J.&nbsp;S. Vitter, *Journal of the ACM* **30** (1983), 231--258.]

```c << Compute the hash code |h| >>=
h = buffer[j];
for(k = j + 1; k < j + l; k++) {
  h = (h + h + buffer[k]) % HASH_PRIME;
}
```
