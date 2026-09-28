# Templates For Competitive Programming
Not all codes are coded by me.

`default.cpp` is the base file. Every other file is a snippet that gets pasted below its
`/*----*/` separator and relies on what it defines (`ll`, `ull`, `LINF`, `MOD`, `EPS`, …).
Unless noted, indices are 0-based and ranges are half-open `[l, r)`.

| File | Contents | Complexity |
| --- | --- | --- |
| [default.cpp](#defaultcpp) | Base template: headers, debug macros, IO helpers, aliases, constants | – |
| [O3.cpp](#o3cpp) | GCC optimization pragmas | – |
| [fastIO.cpp](#fastiocpp) | Buffered integer reader/writer | O(input size) |
| [counting.cpp](#countingcpp) | Modular power, factorials, nCr / nPr / nHr, Catalan | O(n) build, O(1) query |
| [number_theory.cpp](#number_theorycpp) | Linear sieve, Miller–Rabin, Pollard rho | see below |
| [kmp.cpp](#kmpcpp) | Prefix function, pattern matching | O(n + m) |
| [points.cpp](#pointscpp) | 2D point / vector geometry | O(1) per op |
| [segtree.cpp](#segtreecpp) | Iterative segment tree, range add + range sum | O(log n) |
| [hld.cpp](#hldcpp) | Heavy-light decomposition on top of `segtree` | O(log² n) per path op |
| [dijkstra.cpp](#dijkstracpp) | Single-source shortest path | O((V + E) log V) |
| [find_bridges.cpp](#find_bridgescpp) | Tarjan bridge finding | O(V + E) |
| [bipartite_matching.cpp](#bipartite_matchingcpp) | Hopcroft–Karp maximum bipartite matching | O(E √V) |
| [dinic.cpp](#diniccpp) | Dinic max flow + min cut | O(V² E) |
| [mcmf.cpp](#mcmfcpp) | Min-cost max-flow (primal-dual, Dijkstra with potentials) | O(F (V + E) log V) |

---

## default.cpp
Compile locally with `-DEMT` to enable the debug helpers; without it they compile to nothing,
so the file can be submitted as-is. `pre_compile.sh` builds a precompiled `Header/stdc++.h.gch`
with the same flags to speed up local compiles.

| Name | Description |
| --- | --- |
| `debug(x)` | Prints `x = value` to `stderr` in red. Works with pairs and tuples, nested in any order. |
| `print(x)` | Prints every element of a range as `x = [a,b,c]` to `stderr` in yellow. |
| `cin >> pair`, `cin >> vector` | Reads both members / every element (size the vector first). |
| `YN(x)`, `Yn(x)`, `yn(x)` | `"YES"`/`"NO"` in three casings. |
| `ll`, `ull`, `ld`, `uint` | `int64_t`, `uint64_t`, `long double`, `uint32_t`. |
| `base_type<T>` | `T` without cv-qualifiers or references. |
| `EPS`, `INF`, `LINF`, `MOD` | `1e-8`, `0x3F3F3F3F`, `2^62 - 1`, `1e9 + 7`. `INF` is safe to `memset` and to add twice. |

Fast `cin`/`cout` is enabled automatically at start-up (`sync_with_stdio(false)`, untied `cin`).
Therefore do not mix `cin`/`cout` with `scanf`/`printf` or with `fastIO.cpp`.

## O3.cpp
`#pragma GCC optimize` / `target` lines. Put them **above** the includes in `default.cpp`.
`Ofast` enables fast-math, which can change floating-point results; avoid it for precision-sensitive
geometry. The pragmas are GCC-only and ignored by Clang.

## fastIO.cpp
Reads from `stdin` through a 64 KiB `fread` buffer and writes to `stdout` through a 64 KiB buffer
that is flushed automatically at program exit (about 4–5× faster than `getchar`/`putchar`).

| Function | Description |
| --- | --- |
| `bool R(T &x)` | Reads the next integer of any integral type, skipping non-digit characters. Returns `false` at EOF. The full type range is supported, including `INT_MIN`. |
| `W(T x)` | Writes an integer without a separator. |
| `W(char c)`, `W(const char *s)` | Writes a character or a C string. |
| `fast_io::flush()` | Flushes the output buffer manually. |

```cpp
int n; R(n);
while (n--) { ll x; R(x); W(x * 2); W('\n'); }
```
Caveats: the input buffer reads ahead, so it cannot be mixed with `cin`/`scanf`, and it is not suitable for
interactive problems. Output also must not be mixed with `cout`/`printf`. If you must, call `fast_io::flush()` first.

## counting.cpp
Everything is modulo `MOD`, which must be prime.

| Name | Description |
| --- | --- |
| `mpow(a, b)` | `a^b mod MOD`. Negative `a` is allowed. |
| `combinatoric cb(n)` | Precomputes `fac` and `inv_fac` for `0..n-1`. |
| `cb.p(n, m)`, `cb.c(n, m)` | Permutations `nPm` and combinations `nCm`. Return 0 if `m < 0` or `m > n`. |
| `cb.h(n, m)` | Combinations with repetition `C(n + m - 1, m)`. |
| `cb.inv(n)` | Modular inverse of `n` for `1 <= n < size`. |
| `cb.catalan(n)` | `n`-th Catalan number. Needs `size > 2n`. |

## number_theory.cpp
| Name | Description | Complexity |
| --- | --- | --- |
| `prime_sieve ps(n, with_lpf = false)` | Linear sieve over `[0, n)`. `with_lpf` stores least prime factors (4 bytes per number). | O(n) |
| `ps.prime_cnt()`, `ps[i]` | Number of primes below `n` and the `i`-th prime (0-indexed). | O(1) |
| `ps.is_prime(x)` | Primality check for `0 <= x < n`. | O(1) |
| `ps.factorize(x)` | Prime factors of `x` in non-decreasing order (with multiplicity). Requires `with_lpf`. | O(log x) |
| `is_prime(ull x)` | Deterministic Miller–Rabin, correct for all 64-bit values. | O(log x) |
| `factorize(ull x)` | Prime factors via Pollard rho, sorted, with multiplicity. | ~O(x^¼) |
| `mul_mod`, `pow_mod` | 64-bit modular multiply and power using `__int128`. | O(1), O(log b) |

## kmp.cpp
| Function | Description |
| --- | --- |
| `kmp(s)` | Prefix function: `dp[i]` is the length of the longest proper prefix of `s[0..i]` that is also its suffix. |
| `kmp_match(text, pat)` | Start indices of all occurrences of `pat` in `text`, overlaps included. Returns an empty result for an empty `pat`. |

## points.cpp
`point<T>` is a 2D vector. Use an integral `T` whenever possible for exact results.

| Operation | Meaning |
| --- | --- |
| `a + b`, `a - b`, `-a`, `a * k`, `a / k` | Vector arithmetic and scalar multiply or divide. |
| `a * b` | Dot product. |
| `a ^ b` | Cross product (z component). Positive means `b` is counter-clockwise from `a`. |
| `==`, `!=`, `<` | Comparisons; `<` orders lexicographically by `(x, y)`. |
| `dis2()`, `len()` | Squared length and length. |
| `prep()` | Rotated 90° counter-clockwise. |
| `quad()` | Quadrant 1–4, with positive axes assigned to 1 (+x), 2 (+y), 3 (−x), 4 (−y) and 0 for the origin. |
| `angle()` | `atan2(y, x)` in `(-π, π]`. |
| `point<T>::angle_sort_cmp` | Polar-angle comparator starting from +x, counter-clockwise; ties are broken by distance. |
| `ori(a, b, c)` | Orientation of `a → b → c`: 1 counter-clockwise, −1 clockwise, 0 collinear (uses `EPS` for floating `T`). |

`<<` prints `(x, y)` and `>>` reads `x y`. `PI` is `acos(-1)`.

## segtree.cpp
The global `tree` supports range addition and range-sum queries using a bottom-up lazy iterative
implementation. It works for any `n`, not only powers of two.

| Function | Description |
| --- | --- |
| `tree.init(n)` | All zeros. |
| `tree.init(vector<ll> a)` | Builds from initial values in O(n). |
| `tree.edt(l, r, v)` | Adds `v` to `[l, r)`. |
| `tree.que(l, r)` | Returns the sum of `[l, r)`. |

To use a different operation, change `upd`, `pull`, the combine step in `que`, and the empty-range
return value (`// do something!`).

## hld.cpp
Needs a global `const int N` and adjacency `edge[N]` (`vector<int>` per node), and it uses the global
`tree` from `segtree.cpp`.

| Function | Description |
| --- | --- |
| `hld.init(root)` | Decomposes the tree. Call `tree.init(n)` separately. |
| `hld.pos[u]` | Position of node `u` in `tree`. |
| `hld.edt(a, b, v)` | Adds `v` to every node on path `a–b`. |
| `hld.query(a, b)` | Returns the sum over path `a–b`. |
| `hld.lca(a, b)` | Lowest common ancestor. |
| `hld.subtree(u)` | Returns `[l, r)` of `u`'s subtree in `tree`, for subtree updates and queries. |

The DFS is recursive, so a very deep tree (a path of about 10⁶ nodes) may need a bigger stack.

## dijkstra.cpp
```cpp
shortest_path<ll> sp(n);
sp.add_edge(u, v, w);          // directed; add both directions for undirected
auto &dis = sp.run(s);         // unreachable = shortest_path<ll>::T_INF
vector<int> p = sp.path(t);    // s ... t, empty if unreachable
```
All weights must be non-negative.

## find_bridges.cpp
| Function | Description |
| --- | --- |
| `find_bridges fb(n)` | Graph with `n` nodes. |
| `fb.add_edge(u, v)` | Adds an undirected edge. Its id is the insertion order. Multi-edges and self-loops are handled. |
| `fb.find()` | Runs Tarjan and returns the number of bridges. |
| `fb.is_bridge(id)` | Whether edge `id` is a bridge. Call after `find()`. |

## bipartite_matching.cpp
| Function | Description |
| --- | --- |
| `bipartite_matching bm(n, m)` | `n` left and `m` right vertices. |
| `bm.add_edge(u, v)` | Adds an edge from left `u` to right `v`. |
| `bm.match()` | Returns the size of the maximum matching (Hopcroft–Karp). |
| `bm.other(u)` | Right vertex matched to left `u`, or −1. `bm.matr[v]` gives the reverse. |

## dinic.cpp
| Function | Description |
| --- | --- |
| `dinic d(n, s, t)` | Flow network with `n` nodes, source `s` and sink `t`. |
| `d.add_edge(u, v, cap)` | Adds a directed edge. For undirected, add both directions. |
| `d.flow()` | Returns the max flow value. |
| `d.min_cut()` | After `flow()`: `cut[v]` is true if `v` is on the source side of a minimum cut. |
| `d.edges[2 * i]` | The `i`-th added edge. `.flow` holds its flow. |

Runs in O(E √V) on unit-capacity graphs.

## mcmf.cpp
The global object `flow`:

```cpp
flow.init(n, s, t);
flow.add_edge(u, v, cap, cost);
auto [f, c] = flow.flow();   // max flow and its min cost
```
Negative edge costs are allowed as long as there is no negative cycle. One SPFA run computes the initial
potentials, and every augmentation after that uses Dijkstra on reduced costs.
