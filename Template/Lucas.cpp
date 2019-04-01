#include <iostream>
#include <cstdio>

using namespace std;
typedef long long LL;
const int _ = 1e5 + 5;
LL f[_];
int p;
inline LL ksm(LL x, LL y)
{
	LL ans = 1;
	while(y)
	{
		if(y & 1) ans = ans * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ans;
}
inline LL inv(LL x)
{
	return ksm(x, p - 2);
}
LL C(LL n, LL m)
{
	if(n < m) return 0;
	return f[n] * inv(f[n - m]) % p * inv(f[m]) % p;
}
LL lucas(LL n, LL m)
{
	if(m == 0) return 1;
	return C(n % p, m % p) * lucas(n / p, m / p) % p;
}
int main()
{
	int T, n, m;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &n, &m, &p);
		f[0] = 1;
		for(int i = 1; i <= p; i++) f[i] = f[i - 1] * i % p;
		printf("%lld\n", lucas(n + m, m));
	}
}
