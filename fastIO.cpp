namespace fast_io {
    constexpr int BUF_SIZE = 1 << 16;
    char ibuf[BUF_SIZE], obuf[BUF_SIZE];
    int ipos = 0, ilen = 0, opos = 0;
    int gc() {
        if (ipos == ilen) {
            ilen = (int)fread(ibuf, 1, BUF_SIZE, stdin);
            ipos = 0;
            if (ilen <= 0) {
                ilen = 0;
                return EOF;
            }
        }
        return (unsigned char)ibuf[ipos++];
    }
    void flush() {
        fwrite(obuf, 1, opos, stdout);
        opos = 0;
    }
    void pc(char c) {
        if (opos == BUF_SIZE)
            flush();
        obuf[opos++] = c;
    }
    struct flusher { ~flusher() { flush(); } } flusher_;
}
template<typename T>
bool R(T &a) {
    using fast_io::gc;
    int c = gc();
    bool neg = false;
    while (c != EOF && c != '-' && (c < '0' || '9' < c))
        c = gc();
    if (c == EOF)
        return false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    make_unsigned_t<T> u = 0;
    while ('0' <= c && c <= '9')
        u = u * 10 + make_unsigned_t<T>(c - '0'), c = gc();
    a = T(neg ? 0 - u : u);
    return true;
}
template<typename T>
void W(T a) {
    char buf[24];
    int n = 0;
    make_unsigned_t<T> u = make_unsigned_t<T>(a);
    if constexpr (is_signed_v<T>)
        if (a < 0)
            fast_io::pc('-'), u = 0 - u;
    do
        buf[n++] = char('0' + u % 10);
    while (u /= 10);
    while (n)
        fast_io::pc(buf[--n]);
}
void W(char c) { fast_io::pc(c); }
void W(const char *s) {
    while (*s)
        fast_io::pc(*s++);
}
/*********************** Fast IO *********************/
