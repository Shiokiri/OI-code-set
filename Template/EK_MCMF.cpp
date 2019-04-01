#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

const int _ = 50005;
const int inf = 0x3f3f3f3f;
int n, m, s, t;
int ans, maxflow;
int dist[_], incf[_], pre[_], vis[_];
struct Edge { int Nxt, v, flow, cost; } e[_ << 1];
int h[_], p = 1;
void add(int u, int v, int f, int c)
{
	e[++p].Nxt = h[u]; e[p].v = v; e[p].flow = f; e[p].cost = c; h[u] = p;
	e[++p].Nxt = h[v]; e[p].v = u; e[p].flow = 0; e[p].cost = -c; h[v] = p;
}
std::queue<int> q;
bool spfa()
{
	memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    q.push(s); dist[s] = 0; vis[s] = 1;
    incf[s] = inf;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = h[u]; i; i = e[i].Nxt)
        {
            if(!e[i].flow) continue;
            int v = e[i].v;
            if(dist[v] > dist[u] + e[i].cost)
            {
                dist[v] = dist[u] + e[i].cost;
                incf[v] = std::min(incf[u], e[i].flow);
                pre[v] = i;
                if(!vis[v]) vis[v] = 1, q.push(v);
            }
        }
    }
    if(dist[t] == inf) return false;
    else return true;
}
void update()
{
	int u = t;
    while(u != s)
    {
        int i = pre[u];
        e[i].flow -= incf[t];
        e[i ^ 1].flow += incf[t];
        u = e[i ^ 1].v;
    }
    maxflow += incf[t];
    ans += dist[t] * incf[t];
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1, u, v, z, c; i <= m; i++) {
        scanf("%d%d%d%d", &u, &v, &z, &c);
        add(u, v, z, c);
    }
    while(spfa()) update();
    printf("%d %d\n", maxflow, ans);
    return 0;
}
