#include <iostream>
#include <cstdio>

using namespace std;
const int N = 100005;
const int inf = 0x7fffffff;
int n, m;
int ch[N][2], f[N], Size[N], key[N], rev[N], root, sz;
int date[N];
inline int get(int x) {
	return ch[f[x]][1] == x;
}
inline void pushup(int x) {
	Size[x] = Size[ch[x][0]] + Size[ch[x][1]] + 1;
}
inline void pushdown(int x) {
	if(rev[x]) {
		swap(ch[x][0], ch[x][1]);
		rev[ch[x][0]] ^= 1; rev[ch[x][1]] ^= 1; rev[x] = 0;
	}
}
void rotate(int x)
{
	int y = f[x], z = f[y], k = get(x);
	ch[z][ch[z][1] == y] = x; f[x] = z; // x->z
	ch[y][k] = ch[x][k ^ 1]; f[ch[y][k]] = y; // xson->y
	ch[x][k ^ 1] = y; f[y] = x; // y->x
	pushup(y); pushup(x);
}
inline void splay(int x, int goal)
{
	while(f[x] != goal) {
		int y = f[x], z = f[y];
		if(z != goal) get(x) ^ get(y) ? rotate(x) : rotate(y);
		rotate(x);
	}
	if(!goal) root = x;
}
int build(int fa, int l, int r)
{
	if(l > r) return 0;
	int mid = (l + r) >> 1, p = ++sz;
	key[p] = date[mid], f[p] = fa, rev[p] = 0;
	ch[p][0] = build(p, l, mid - 1);
	ch[p][1] = build(p, mid + 1, r);
	pushup(p); return p;
}
inline int find(int k)
{
	int p = root;
	while(true) {
		pushdown(p);
		if(k <= Size[ch[p][0]]) p = ch[p][0];
		else {
			k -= Size[ch[p][0]] + 1;
			if(!k) return p;
			p = ch[p][1];
		}
	}
}
void print(int p) {
	pushdown(p);
	if(ch[p][0]) print(ch[p][0]);
	if(key[p] != -inf && key[p] != inf) printf("%d ", key[p]);
	if(ch[p][1]) print(ch[p][1]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) date[i + 1] = i;
	date[1] = -inf; date[n + 2] = inf;
	root = build(0, 1, n + 2);
	for(int i = 1, x, y; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		int x1 = find(x), y1 = find(y + 2); // (x - 1) + 1  (y + 1) + 1
		splay(x1, 0);
		splay(y1, x1);
		rev[ch[ch[root][1]][0]] ^= 1;
	}
	print(root);
	return 0;
}
