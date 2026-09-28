template<typename T>
void R(T &a) {
    int c = getchar();
    bool neg = false;
    while (c != EOF && c != '-' && (c < '0' || '9' < c))
        c = getchar();
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    make_unsigned_t<T> u = 0;
    while ('0' <= c && c <= '9')
        u = u * 10 + make_unsigned_t<T>(c - '0'), c = getchar();
    a = T(neg ? 0 - u : u);
}
template<typename T>
void W(T a) {
    char buf[24];
    int n = 0;
    make_unsigned_t<T> u = make_unsigned_t<T>(a);
    if constexpr (is_signed_v<T>)
        if (a < 0)
            putchar('-'), u = 0 - u;
    do
        buf[n++] = char('0' + u % 10);
    while (u /= 10);
    while (n)
        putchar(buf[--n]);
}
/*********************** Fast IO *********************/
