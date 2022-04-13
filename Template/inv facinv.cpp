#include <cstdio>
#include <iostream>
#define LL long long

using namespace std;
const int N = 1000005;
const LL P = 1000000007;
LL n, k, d, base, ans;
LL fac[N], inv[N], facInv[N];

LL ksm(LL a, LL b)
{
	LL ret = 1;
	for (; b; b >>= 1, a = a * a % P)
		if (b & 1)
			ret = ret * a % P;
	return ret;
}
LL C(LL a, LL b)
{
	return fac[a] * facInv[a - b] % P * facInv[b] % P;
}
int main()
{
	scanf("%lld%lld", &n, &k);
	inv[0] = inv[1] = 1;
	for (LL i = 2; i <= n; i++) inv[i] = (-P / i * inv[P % i] + P) % P;
	fac[0] = facInv[0] = 1;
	for (LL i = 1; i <= n; i++)
	{
		fac[i] = fac[i - 1] * i % P;
		facInv[i] = facInv[i - 1] * inv[i] % P;
	}
	base = 2;
	d = (n - k) & 1 ? -1 : 1;
	for (LL i = n; i >= k; i--)
	{
		ans = (1ll * d * C(i, k) * C(n, i) % P * (base - 1) % P + ans + P) % P;
		base = 1ll * base * base % P;
		d = -d;
	}
	printf("%lld\n", ans);
	return 0;
}
