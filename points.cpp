template<typename T> requires is_arithmetic_v<T>
struct point {
    T x, y;
    point() : x(0), y(0) {}
    point(const T &a, const T &b) : x(a), y(b) {}
    point(const pair<T, T> &res) : x(res.first), y(res.second) {}

    point operator+(const point &b) const { return point(x + b.x, y + b.y); }
    point operator-(const point &b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    point operator*(const T &k) const { return point(x * k, y * k); }
    point operator/(const T &k) const { return point(x / k, y / k); }

    T operator*(const point &b) const { return x * b.x + y * b.y; }
    T operator^(const point &b) const { return x * b.y - y * b.x; }
    // lexicographic by (x, y); also provides !=, <, <=, >, >=
    auto operator<=>(const point &b) const = default;
    bool operator==(const point &b) const = default;

    T dis2() const { return (*this) * (*this); }
    double len() const { return sqrt((double)dis2()); }
    point prep() const { return point(-y, x); } // 左旋法向量
    int quad() const {
        if (x == 0 && y == 0)
            return 0;
        if (y == 0)
            return x > 0 ? 1 : 3;
        if (x == 0)
            return y > 0 ? 2 : 4;
        if (x > 0)
            return y > 0 ? 1 : 4;
        return y > 0 ? 2 : 3;
    } // 象限
    double angle() const { return atan2(y, x); } // (-pi, pi]

    friend ostream& operator<<(ostream &out, const point &res) {
        return out << '(' << res.x << ", " << res.y << ')';
    }
    friend istream& operator>>(istream &in, point &res) {
        return in >> res.x >> res.y;
    }

    static bool angle_sort_cmp(const point &a, const point &b) {
        if (a.quad() != b.quad())
            return a.quad() < b.quad();
        if ((a ^ b) == 0)
            return a.dis2() < b.dis2();
        return (a ^ b) > 0;
    } // 極角排序，角度相同近的在前
};
// orientation of a -> b -> c: 1 counter-clockwise, -1 clockwise, 0 collinear
template<typename T>
int ori(const point<T> &a, const point<T> &b, const point<T> &c) {
    T v = (b - a) ^ (c - a);
    if constexpr (is_floating_point_v<T>)
        return v > EPS ? 1 : v < -EPS ? -1 : 0;
    else
        return (v > 0) - (v < 0);
}
const double PI = acos(-1.0);
/*
 * + - * / : vector ops (a * b is dot, a * k is scale), ^ : cross
 * dis2() / len() / prep() / quad() / angle()
 * sort(v.begin(), v.end(), point<T>::angle_sort_cmp): polar sort
 * ori(a, b, c): 1 ccw, -1 cw, 0 collinear
 */
/*********** Geometry--Points *************/
