#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;
const int N = 100005;
const int inf = 0x3f3f3f3f;
int n,m; string tp;
int p[N],father[N];
struct Edge {
	int Next,to;
}e[N<<1];
int head[N],num;
void add(int from,int to)
{
	e[++num].Next = head[from];
	e[num].to = to;
	head[from] = num;
}
int a[N];
long long dp[N][2];
void dfs(int u,int f)
{
	for(int i = head[u]; i; i = e[i].Next)
		if(e[i].to != f)
	{
		int v = e[i].to;
		dfs(v, u);
		if(a[u] == -1) {
			dp[u][1] = inf;
			dp[u][0] += dp[v][1];
		}
		else if(a[u] == 1) {
			dp[u][1] += min(dp[v][1],dp[v][0]);
			dp[u][0] = inf;
		}
		else {
			dp[u][1] += min(dp[v][1],dp[v][0]);
			dp[u][0] += dp[v][1];
		}
	}
	if(e[head[u]].to == f && e[head[u]].Next == 0) {
		if(a[u] == -1) {
			dp[u][1] = inf;
		}
		else if(a[u] == 1) {
			dp[u][0] = inf;
		}
	}
}
int main()
{
	freopen("defense.in","r",stdin);
	freopen("defense.out","w",stdout);
	cin >> n >> m >> tp;
	for(int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	for(int i = 1,u,v; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		add(u,v); add(v,u);
		father[v] = u;
	}
	if(tp[1] == 1)
	{
		dfs(1, 0);
		int x,xx,y,yy;
		for(int i = 1; i <= m; i++)
		{
			scanf("%d%d%d%d", &x, &y, &xx, &yy);
			printf("%lld\n", dp[1][1]);
		}
		return 0;
	}
	for(int i = 1,x,y,xx,yy; i <= m; i++)
	{
		scanf("%d%d%d%d", &x, &y, &xx, &yy);
		if((father[x] == xx || father[xx] == x) && y == 0 && yy == 0) {
			printf("-1\n");
			continue;
		}
		if(y == 0) a[x] = -1;
		if(y == 1) a[x] = 1;
		if(yy == 0) a[xx] = -1;
		if(yy == 1) a[xx] = 1;
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= n; i++)
			dp[i][1] = p[i];
		dfs(1,0);
		a[x] = a[xx] = 0;
		printf("%lld\n", min(dp[1][0], dp[1][1]));
	}
	return 0;
}
/*
5 3 C3
2 4 1 3 9
1 5
5 2
5 3
3 4
1 0 3 0
2 1 3 1
1 0 5 0
*/
