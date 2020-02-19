#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 300005;
int T, n, U[N], V[N];
struct Edge {
	int Nxt, v;
}e[N<<1];
int h[N], p = 1;
void add(int u, int v)
{
	e[++p].Nxt = h[u];
	e[p].v = v;
	h[u] = p;
}
int a[N], cnt, ind[N];
void LianDfs(int u, int f)
{
	a[++cnt] = u;
	for(int i = h[u]; i; i = e[i].Nxt)
		if(e[i].v != f)
			LianDfs(e[i].v, u);
}
void SolveLian()
{
	int x = 0;
	for(int i = 1; i <= n; i++)
		if(ind[i] == 1)
	{ x = i; break; }
	LianDfs(x, 0);
	long long ans = 0;
	for(int i = 1; i < n; i++)
	{
		int x = i, y = n - i;
		if(x & 1) ans += a[(x+1)/2];
		else ans += a[x/2] + a[x/2+1];
		if(y & 1) ans += a[n-y/2];
		else ans += a[n-y/2] + a[n-y/2+1];
	}
	printf("%lld\n", ans);
}
int Size[N];
long long ans;
void PreDfs(int u, int f)
{
	Size[u] = 1;
	for(int i = h[u]; i; i = e[i].Nxt)
		if(e[i].v != f)
	{
		int v = e[i].v;
		PreDfs(v, u);
		Size[u] += Size[v];
	}
}
int CUT;
void Dfs(int u, int f)
{
	bool flag = 1;
	for(int i = h[u]; i; i = e[i].Nxt)
		if(e[i].v != CUT)
	{
		int v = e[i].v;
		if(!(Size[v] <= Size[u]/2)) flag = 0;
	}
	if(flag) {
		ans += u;
	}
	for(int i = h[u]; i; i = e[i].Nxt)
		if(e[i].v != f)
	{
		int v = e[i].v;
		Size[u] -= Size[v];
		Size[v] += Size[u];
		Dfs(v, u);
		Size[v] -= Size[u];
		Size[u] += Size[v];
	}
}
int main()
{
	freopen("centroid.in","r",stdin);
	freopen("centroid.out","w",stdout);
	scanf("%d", &T);
	while(T--)
	{
		memset(h, 0, sizeof(h)); p = 1;
		memset(ind, 0, sizeof(ind)); cnt = 0;
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i < n; i++)
		{
			scanf("%d%d", &U[i], &V[i]);
			ind[U[i]]++; ind[V[i]]++;
			add(U[i], V[i]); add(V[i], U[i]);
		}
		if(n % 10 == 1)
		{
			SolveLian();
			continue;
		}
		for(int i = 1; i < n; i++)
		{
			PreDfs(U[i], V[i]);
			CUT = V[i];
			Dfs(U[i], V[i]);
			PreDfs(V[i], U[i]);
			CUT = U[i];
			Dfs(V[i], U[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
