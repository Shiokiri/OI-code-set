#include <iostream>
#include <cstdio>

using namespace std;
long long n,a[100005],last,ans;
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		if(a[i] > last) ans += a[i] - last;
		last = a[i];
	}
	printf("%lld\n", ans);
	return 0;
}
