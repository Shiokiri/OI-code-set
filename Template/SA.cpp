#include <iostream> 
#include <cstdio>
#include <string>
#define R register int

using namespace std;
const int N = 1000005;
string s;
int n, m, sa[N], rk[N], tp[N], c[N];
void _sort() {
	for(R i = 1; i <= m; ++i) c[i] = 0;
	for(R i = 1; i <= n; ++i) c[rk[i]]++;
	for(R i = 1; i <= m; ++i) c[i] += c[i - 1];
	for(R i = n; i >= 1; --i) sa[c[rk[tp[i]]]--] = tp[i];
}
void SA() {
	m = 150;
	for(R i = 1; i <= n; ++i) rk[i] = s[i - 1], tp[i] = i;
	_sort();
	for(R w = 1, p = 0; p < n && w <= n; m = p, w <<= 1) {
		p = 0;
		for(R i = 1; i <= w; ++i) tp[++p] = n - w + i;
		for(R i = 1; i <= n; ++i) if(sa[i] > w) tp[++p] = sa[i] - w;
		_sort();
		swap(tp, rk);
		rk[sa[1]] = p = 1;
		for(R i = 2; i <= n; ++i)
			rk[sa[i]] = (tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + w] == tp[sa[i] + w])
			? p : ++p;
	}
}
int Height[N];
void Get() {
	int j, k = 0;
	for(int i = 1; i <= n; i++) {
		if(k) k--;
		j = sa[rk[i] - 1];
		while(s[i + k - 1] == s[j + k - 1]) ++k;
		Height[rk[i]] = k;
	}
}
int main()
{
	cin >> n >> s;
	SA();
	Get();
	long long ans = 1LL * n * (n + 1) / 2;
	for(int i = 1; i <= n; i++)
		ans -= Height[rk[i]];
	cout << ans << endl;
	return 0;
}
