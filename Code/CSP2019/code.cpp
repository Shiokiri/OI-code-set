#include <iostream>
#include <cstdio>
#define ull unsigned long long

using namespace std;
int n, res[105];
ull k;
ull f(ull l, ull r, ull al, ull ar, bool fl)
{
//	cout << l << " " << r << " " << al <<" " << ar << endl;
//	cout << fl << endl;
	ull mid = (l + r) >> 1;
	ull amid = (al + ar) >> 1;
	if(r-l == 0) return amid;
	if(k <= mid) {
		if(fl == 0)
			return f(l, mid, al, amid, fl);
		else if(fl == 1)
			return f(l, mid, amid+1, ar, fl^1);
	}
	else {
		if(fl == 0)
			return f(mid+1, r, amid+1, ar, fl^1);
		else if(fl == 1)
			return f(mid+1, r, al, amid, fl);
	}
}
int main()
{
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
	cin >> n >> k;
	ull ans = f(0, (1LL<<n)-1, 0, (1LL<<n)-1, 0);
	for(int i = 1; i <= n; i++)
	{
		res[i] = ans & 1;
		ans >>= 1;
	}
	for(int i = n; i >= 1; i--) printf("%d", res[i]);
	return 0;
}