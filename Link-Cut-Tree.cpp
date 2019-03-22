#include <cstdio>
#include <iostream>
#define R register int
#define ls c[x][0]
#define rs c[x][1]

using namespace std;
const int _ = 3e5 + 5;
int f[_], c[_][2], v[_], s[_], st[_];
bool r[_];
inline bool nroot(R x) // notroot = 1 / isroot = 0
{
	return c[f[x]][0] == x || c[f[x]][1] == x;
}
inline void pushup(R x)
{
	s[x] = s[ls] ^ s[rs] ^ v[x];
}
inline void pushr(R x)
{ 
	swap(ls, rs); r[x] ^= 1;
}
inline void pushdown(R x)
{ 
	if(r[x]) { 
		if(ls) pushr(ls); 
		if(rs) pushr(rs);
		r[x] = 0;
	}
}
inline void pushall(R x)
{ 
	if(nroot(x)) pushall(f[x]);
	pushdown(x);
}
inline void rotate(R x)
{
    R y = f[x], z = f[y], k = c[y][1] == x, w = c[x][!k];
    if(nroot(y)) c[z][c[z][1] == y] = x; c[x][!k] = y; c[y][k] = w;
    if(w) f[w] = y; f[y] = x; f[x] = z;
	pushup(y);
}
inline void splay(R x)
{
    R y, z; pushall(x);
    while(nroot(x))
	{
        y = f[x]; z = f[y];
        if(nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y); //Ë«Ðý ²Î¿¼splayÍ¼
        rotate(x);
    }
	pushup(x);
}
inline void access(R x)
{
	for(R y = 0; x; x = f[y = x])
		splay(x), rs = y, pushup(x);
}
inline void makeroot(R x)
{
	access(x); splay(x);
	pushr(x);
}
inline int findroot(R x)
{
	access(x); splay(x);
	while(ls) pushdown(x), x = ls; splay(x);
	return x;
}
inline void split(R x, R y) 
{ 
	makeroot(x); access(y);
	splay(y);
}
inline void link(R x, R y)
{
	makeroot(x);
	if(findroot(y) != x) f[x] = y;
}
inline void cut(R x, R y) {
    makeroot(x);
	if(findroot(y) != x || f[y] != x || c[y][0]) return;
    f[y] = c[x][1] = 0;
	pushup(x);
}
int main()
{
    R n, m, opt, x, y;
    scanf("%d%d", &n, &m);
    for(R i = 1; i <= n; ++i) scanf("%d", &v[i]);
    while(m--) {
        scanf("%d%d%d", &opt, &x, &y);
        if(opt == 0) split(x, y), printf("%d\n", s[y]);
        else if(opt == 1) link(x, y);
        else if(opt == 2) cut(x, y);
        else if(opt == 3) splay(x), v[x] = y;
    }
    return 0;
}
