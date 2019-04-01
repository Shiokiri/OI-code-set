#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1e5 + 5, _ = 22 * 200005;
int n, m;
int L[_], R[_], fa[_], dep[_];
int root[_], cnt;
#define mid ((l + r) >> 1)
#define lson L[p], l, mid
#define rson R[p], mid + 1, r
void build(int &p, int l, int r)
{
	p = ++cnt;
	if(l == r) { fa[p] = l; return; }
	build(lson); build(rson);
}
void merge(int last, int &p, int l, int r, int pos, int Fa)
{
	p = ++cnt; L[p] = L[last]; R[p] = R[last];
	if(l == r) { fa[p] = Fa; dep[p] = dep[last]; return; }
	if(pos <= mid) merge(L[last], lson, pos, Fa);
	else merge(R[last], rson, pos, Fa);
}
void update(int p, int l, int r, int pos)
{
	if(l == r) { dep[p]++; return; }
	if(pos <= mid) update(lson, pos);
	else update(rson, pos);
}
int query(int p, int l, int r, int pos)
{
	if(l == r) return p;
	if(pos <= mid) return query(lson, pos);
	else return query(rson, pos);
}
int find(int p, int pos)
{
	int now = query(p, 1, n, pos);
	if(fa[now] == pos) return now;
	return find(p, fa[now]);
}
#undef mid
#undef lson
#undef rson
int main()
{
	scanf("%d%d", &n, &m);
	build(root[0], 1, n);
	int opt, x, y;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &opt, &x);
		if(opt == 1)
		{
			scanf("%d", &y);
			int posx, posy;
			root[i] = root[i - 1];
			posx = find(root[i], x); posy = find(root[i], y);
			if(fa[posx] != fa[posy])
			{
				if(dep[posx] > dep[posy]) swap(posx, posy);
				merge(root[i - 1], root[i], 1, n, fa[posx], fa[posy]);
				if(dep[posx] == dep[posy]) update(root[i], 1, n, fa[posy]);
			}
		}
		else if(opt == 2) root[i] = root[x];
		else if(opt == 3)
		{
			scanf("%d", &y);
			root[i] = root[i - 1];
			int posx, posy;
			posx = find(root[i], x); posy = find(root[i], y);
			if(fa[posx] == fa[posy]) puts("1");
			else puts("0");
		}
	}
	return 0;
}
