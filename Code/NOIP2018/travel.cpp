#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
const int N = 10005;
const int inf = 0x3f3f3f3f;
int n,m;
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
int vis[N],ans[N],T;
void dfs(int u, int father)
{
	ans[++T] = u;
	int tot = 0, Min = inf, v = 0;
	for(int i = head[u]; i; i = e[i].Next)
		if(e[i].to != father && !vis[e[i].to])
			tot ++;
	for(int w = 1; w <= tot; w++)
	{
		Min = inf;
		for(int i = head[u]; i; i = e[i].Next)
		{
			v = e[i].to;
			if(!vis[v]) {
				Min = min(Min, v);
			}
		}
		vis[Min] = 1;
		dfs(Min, u);
	}
}
priority_queue<int,vector<int>,greater<int> > q;
//void dfs2(int u, int k)
//{
//	cout << u << " " << k << endl;
//	ans[k] = min(ans[k], u);
//	int t = 0;
//	for(int i = head[u]; i; i = e[i].Next)
//	{
//		t++;
//		int v = e[i].to;
//		if(vis[v]) continue;
//		vis[v] = 1;
//		dfs2(v,k+t);
//		vis[v] = 0;
//	}
//}
//void dfs2(int u) {
//	if(vis[u]) continue;
//	vis[u] = 1;
//	ans[++T] = u;
//	for(int i = head[u]; i; i = e[i].Next)
//}
int main()
{
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1,u,v; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		add(u,v); add(v,u);
	}
	if(m == n - 1)
	{
		vis[1] = 1;
		dfs(1, 0);
		for(int i = 1; i <= T; i++)
			printf("%d ", ans[i]);
		return 0;
	}
	else if(m == n)
	{
		q.push(1);
		vis[1] = 1;
		while(!q.empty())
		{
			int u = q.top(); q.pop();
			vis[u] = 1;
			ans[++T] = u;
			for(int i = head[u]; i; i = e[i].Next)
			{
				int v = e[i].to;
				if(vis[v]) continue;
				vis[v] = 1;
				q.push(v);
			}
		}
		for(int i = 1; i <= T; i++)
			printf("%d ", ans[i]);
		return 0;
//		vis[1] = 1;
//		memset(ans, 0x3f, sizeof(ans));
//		dfs2(1, 1);
//		for(int i = 1; i <= n; i++)
//			printf("%d ", ans[i]);
//		return 0;
//		dfs2(1);
//		for(int i = 1; i <= T; i++)
//			printf("%d ", ans[i]);
//		return 0;
	}
	return 0;
}
/*
6 5
1 3
2 3
2 5
3 4
4 6
*/
