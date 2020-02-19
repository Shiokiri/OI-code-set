#include <iostream>
#include <cstdio>
#define ll long long

using namespace std;
const unsigned long long inf = 4e18;
const int N = 5005;
int n, tp;
ll a[N];
unsigned long long dp[N][N], S[N][N], sum[N];
inline ll p(ll x) { return x * x; }
int main()
{
	freopen("partition.in","r",stdin);
	freopen("partition.out","w",stdout);
	scanf("%d%d", &n, &tp);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dp[i][j] = inf, S[i][j] = inf;
	for(int i = 1; i <= n; i++)
		dp[i][1] = p(sum[i]), S[i][1] = sum[i];
	for(int i = 1; i <= n; i++)
		for(int k = 2; k <= n; k++)
			for(int j = k-1; j <= i-1; j++)
				if(sum[i] - sum[j] >= S[j][k-1] && dp[j][k-1] != inf)
	{
		if(dp[i][k] >= dp[j][k-1] + p(sum[i] - sum[j]));
		{
			dp[i][k] = dp[j][k-1] + p(sum[i] - sum[j]);
			S[i][k] = sum[i] - sum[j];
		}
	}
	unsigned long long ans = inf;
	for(int i = 1; i <= n; i++) ans = min(ans, dp[n][i]);
	cout << ans << endl;
	return 0;
}
