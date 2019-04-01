#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

const int inf = 0x3fffffff;
const int N = 10005, M = 100005;
int n, m, s, t, maxflow;
int d[N];
struct Edge {
	int Nxt, v, flow;
}e[M << 1];
int h[N], p = 1;
void add(int u, int v, int z)
{
	e[++p].Nxt = h[u]; e[p].v = v; e[p].flow = z; h[u] = p;
	e[++p].Nxt = h[v]; e[p].v = u; e[p].flow = 0; h[v] = p;
}
std::queue<int> q;
bool bfs()
{
	memset(d, 0, sizeof(d));
	while(!q.empty()) q.pop();
	q.push(s); d[s] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = h[u]; i; i = e[i].Nxt)
			if(e[i].flow && !d[e[i].v])
		{
			q.push(e[i].v);
			d[e[i].v] = d[u] + 1;
			if(e[i].v == t) return true;
		}
	}
	return false;
}
int dinic(int u, int flow)
{
	if(u == t) return flow;
	int rest = flow, k;
	for(int i = h[u]; i && rest; i = e[i].Nxt)
		if(e[i].flow && d[e[i].v] == d[u] + 1)
	{
		k = dinic(e[i].v, std::min(rest, e[i].flow));
		if(!k) d[e[i].v] = 0;
		e[i].flow -= k;
		e[i ^ 1].flow += k;
		rest -= k;
	}
	return flow - rest;
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1, u, v, z; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &z);
        add(u, v, z);
    }
    int flow = 0;
    while(bfs())
        while(flow = dinic(s, inf)) maxflow += flow;
    printf("%d\n", maxflow);
    return 0;
}
