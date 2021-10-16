void R(int &a) {
	char c = getchar();
	a = 0;
	bool neg = 0;
	while(c != '-' && (c < '0' || c > '9'))
		c = getchar();
	if(c == '-') {
		neg = 1;
		c = getchar();
	}
	while('0' <= c && c <= '9')
		a = (a * 10 + (c ^ 48)), c = getchar();
	if(neg)
		a = -a;
}
char buffer[20];
void W(int a) {
	if(!a) {
		putchar('0');
		return;
	}
	int n = 0;
	if(a < 0)
		putchar('-'), a = -a;
	while(a)
		buffer[n++] = a % 10, a /= 10;
	for(n--; ~n; n--)
		putchar(buffer[n] | 48);
}
/*********************** Fast IO *********************/
