#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
const int N = 205;
const double inf = 1e12, eps = 1e-8;
int n, m, s, t, a[N][N], b[N][N];
int maxflow; double ans;
struct Edge {
	int Next, v, flow; double cost;
}e[N * N];
int head[N], p = 1;
void add(int u, int v, int z, double c)
{
	e[++p].Next = head[u];
	e[p].v = v;
	e[p].flow = z;
	e[p].cost = c;
	head[u] = p;
}
int vis[N], incf[N], pre[N]; double dis[N];
queue<int> q;
bool spfa()
{
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i <= t; i++) dis[i] = -inf;
	q.push(s); dis[s] = 0; vis[s] = 1; incf[s] = 0x7fffffff;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u]; i; i = e[i].Next)
		{
			int v = e[i].v;
			if(dis[v] < dis[u] + e[i].cost && e[i].flow)
			{
				dis[v] = dis[u] + e[i].cost;
				incf[v] = min(incf[u], e[i].flow);
				pre[v] = i;
				if(!vis[v]) vis[v] = 1, q.push(v);
			}
		}
	}
	if(dis[t] == -inf) return false;
	else return true;
}
void update()
{
	int u = t;
	while(u != s) {
		int i = pre[u];
		e[i].flow -= incf[t];
		e[i ^ 1].flow += incf[t];
		u = e[i ^ 1].v;
	}
	maxflow += incf[t];
	ans += incf[t] * dis[t];
}
bool check(double c)
{
	memset(head, 0, sizeof(head)); p = 1;
	for(int i = 1; i <= n; i++) add(s, i, 1, 0), add(i, s, 0, 0);
	for(int i = n + 1; i <= 2 * n; i++) add(i, t, 1, 0), add(t, i, 0, 0);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			add(i, j + n, 1, 1.0 * a[i][j] - 1.0 * b[i][j] * c),
			add(j + n, i, 0, -(1.0 * a[i][j] - 1.0 * b[i][j] * c));
	maxflow = 0; ans = 0;
	while(spfa()) update();
	return abs(ans) <= eps || ans > eps; // ans >= 0
}
int main()
{
	scanf("%d", &n);
	s = 0; t = 2 * n + 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &b[i][j]);
	double l = 0, r = 1e6 + 5, mid = 0;
	while(r - l >= eps)
	{
		mid = (l + r) / 2;
		if(check(mid)) l = mid; // C >= 0
		else r = mid;
	}
	printf("%.6lf\n", r);
	return 0;
}
