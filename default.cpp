/*
--------------              |   /
      |                     |  /
      |                     | /
      |             *       |/          |    |         ------            *
      |                     |           |    |        /      \
      |             |       |\          |    |       |       |\          |
   \  |             |       | \         |    |       |       | \         |
    \ |             |       |  \        |    |        \     /   \        |
     V              |       |   \        \__/|         -----     \       |
*/
#ifdef EMT
#include "Header/stdc++.h"
#else
#include <bits/stdc++.h>
#endif
using namespace std;

#ifdef EMT
#define debug(x) cerr << "\033[1;31m" << #x << " = " << (x) << "\033[0m\n"
#define print(x) print_range_(#x, begin(x), end(x))
template<typename T, typename T2>
ostream& operator<<(ostream &os, const pair<T, T2> &obj);
template<typename... T>
ostream& operator<<(ostream &os, const tuple<T...> &obj);
template<ranges::range R> requires (!is_convertible_v<const R&, string_view>)
ostream& operator<<(ostream &os, const R &obj);

template<typename T, typename T2>
ostream& operator<<(ostream &os, const pair<T, T2> &obj) {
    return os << '{' << obj.first << ',' << obj.second << '}';
}
template<typename... T>
ostream& operator<<(ostream &os, const tuple<T...> &obj) {
    os << '{';
    apply([&os](const auto &...args) {
        size_t i = 0;
        ((os << (i++ ? "," : "") << args), ...);
    }, obj);
    return os << '}';
}
template<ranges::range R> requires (!is_convertible_v<const R&, string_view>)
ostream& operator<<(ostream &os, const R &obj) {
    os << '[';
    for (bool first = true; const auto &x : obj)
        os << (first ? "" : ",") << x, first = false;
    return os << ']';
}
template<typename It>
void print_range_(const char *s, It l, It r) {
    cerr << "\033[1;33m" << s << " = [";
    for (bool first = true; l != r; ++l, first = false)
        cerr << (first ? "" : ",") << *l;
    cerr << "]\033[0m\n";
}
#else
#define debug(x) (void)0
#define print(x) (void)0
#endif

template<typename T, typename T2>
istream& operator>>(istream &is, pair<T, T2> &obj) {
    return is >> obj.first >> obj.second;
}
template<typename T>
istream& operator>>(istream &is, vector<T> &obj) {
    for (auto &x : obj)
        is >> x;
    return is;
}

#define YN(x) ((x) ? "YES" : "NO")
#define Yn(x) ((x) ? "Yes" : "No")
#define yn(x) ((x) ? "yes" : "no")
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using uint = uint32_t;
template<typename T>
using base_type = remove_cvref_t<T>;
constexpr double EPS = 1e-8;
constexpr int INF    = 0x3F3F3F3F;
constexpr ll LINF    = (1LL << 62) - 1; // 4611686018427387903
constexpr int MOD    = 1'000'000'007;
static const bool FAST_IO = [] {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return true;
}();
/*--------------------------------------------------------------------------------------*/

signed main() {

}
