#include <iostream>
#include <cstdio>
#define ll long long

using namespace std;
const int mod = 998244353;
int n, m;
ll a[105][2005], sum[105][2005];
ll dp[41][41][41];
void Solve2()
{
	dp[0][0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= i; j++)
			for(int k = 0; j+k <= i; k++)
	{
		dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k]) % mod;
		if(j-1 >= 0) dp[i][j][k] = (dp[i][j][k] + dp[i-1][j-1][k] * a[i][1] % mod) % mod;
 		if(k-1 >= 0) dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k-1] * a[i][2] % mod) % mod;
	}
	ll ans = 0;
	for(int j = 0; j <= n; j++)
		for(int k = 0; j + k <= n; k++)
			if(j <= (j+k)/2 && k <= (j+k)/2 && j+k >= 2)
				ans = (ans + dp[n][j][k]) % mod;
	printf("%lld\n", ans);
}
ll f[41][41][41][41];
void Solve3()
{
	f[0][0][0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= i; j++)
			for(int k = 0; j+k <= i; k++)
				for(int l = 0; j+k+l <= i; l++)
	{
		f[i][j][k][l] = (f[i][j][k][l] + f[i-1][j][k][l]) % mod; 
		if(j-1 >= 0) f[i][j][k][l] = (f[i][j][k][l] + f[i-1][j-1][k][l] * a[i][1] % mod) % mod;
 		if(k-1 >= 0) f[i][j][k][l] = (f[i][j][k][l] + f[i-1][j][k-1][l] * a[i][2] % mod) % mod;
		if(l-1 >= 0) f[i][j][k][l] = (f[i][j][k][l] + f[i-1][j][k][l-1] * a[i][3] % mod) % mod;
	}
	ll ans = 0;
	for(int j = 0; j <= n; j++)
		for(int k = 0; j + k <= n; k++)
			for(int l = 0; j + k + l <= n; l++)
				if(j <= (j+k+l)/2 && k <= (j+k+l)/2 && l <= (j+k+l)/2 && j+k+l >= 2)
					ans = (ans + f[n][j][k][l]) % mod;
	printf("%lld\n", ans);
}
int main()
{
	freopen("meal.in","r",stdin);
	freopen("meal.out","w",stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
	{
		scanf("%lld", &a[i][j]);
		sum[i][j] = (sum[i-1][j] + a[i][j]) % mod;
	}
	if(m == 2)
	{
		Solve2();
		return 0;
	}
	if(m == 3)
	{
		Solve3();
		return 0;
	}
	return 0;
}
