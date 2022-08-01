template<typename T>
struct point {
    T x, y;
    point(): x(0), y(0) { }
    point(const T &a, const T &b): x(a), y(b) { }
    point(const pair<T, T> &res): x(res.first), y(res.second) { }
    
    point operator+(point b) const { return point(x + b.x, y + b.y); }
    point operator-(point b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }

    T operator*(point b) const { return x * b.x + y * b.y; }
    T operator^(point b) const { return x * b.y - y * b.x; }
    bool operator==(point b) const { return x == b.x && y == b.y; }
    bool operator!=(point b) const { return x != b.x || y != b.y; }
    bool operator<(point b) const { return x == b.x ? x < b.x : y < b.y; }

    T dis2() { return (*this) * (*this); }
    point prep() { return point(-y, x); } // 左旋法向量
    int quad() {
        if(x == 0 && y == 0)
            return 0;
        if(y == 0)
            return x > 0 ? 1 : 3;
        if(x == 0)
            return y > 0 ? 2 : 4;
        if(x > 0)
            return y > 0 ? 1 : 4;
        return y > 0 ? 2 : 3;
    } // 象限
    double angle() { return atan2(y, x); } // (-pi, pi]
    
    friend ostream& operator<<(ostream &out, point &res) {
        out << '(' << res.x << ", " << res.y << ')';
        return out;
    }
    friend istream& operator>>(istream &in, point &res) {
        in >> res.x >> res.y;
        return in;
    }

    static bool angle_sort_cmp(point a, point b) {
        if(a.quad() != b.quad())
            return a.quad() < b.quad();
        if((a ^ b) == 0)
            return a.dis2() < b.dis2();
        return (a ^ b) > 0;
    } // 極角排序，角度相同近的在前
};
const double PI = acos(-1);
/*********** Geometry--Points *************/
