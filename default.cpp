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
#define debug(...) debug_(#__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)
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
// debug(a, b, ...) prints "a = .. | b = ..", names are split on commas outside brackets and quotes
template<typename... T>
void debug_(string_view names, const T &...args) {
    size_t pos = 0;
    [[maybe_unused]] auto next_name = [&] {
        size_t st = min(names.find_first_not_of(' ', pos), names.size()), j = st;
        int depth = 0;
        for (char quote = 0; j < names.size(); j++) {
            char c = names[j];
            if (quote) {
                if (c == '\\')
                    j++;
                else if (c == quote)
                    quote = 0;
            } else if (c == '"' || c == '\'')
                quote = c;
            else if (c == '(' || c == '[' || c == '{')
                depth++;
            else if (c == ')' || c == ']' || c == '}')
                depth--;
            else if (c == ',' && !depth)
                break;
        }
        pos = j + 1;
        return names.substr(st, j - st);
    };
    cerr << "\033[1;31m";
    ((cerr << (pos ? " | " : "") << next_name() << " = " << args), ...);
    cerr << "\033[0m\n";
}
#else
#define debug(...) (void)0
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
