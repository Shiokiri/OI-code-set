#include <iostream>
#include <cstdio>

using namespace std;
const int N = 100005;
const int inf = 0x7fffffff;
int n, m;
int ch[N][2], f[N], siz[N], cnt[N], val[N], root, sz;
inline int get(int x) {
    return ch[f[x]][1] == x;
}
inline int pushup(int x) {
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];
}
inline void rotate(int x) {
    int y = f[x], z = f[y], k = get(x);
    ch[z][ch[z][1] == y] = y; f[y] = z;
    ch[y][k] = ch[x][!k]; f[ch[y][k]] = y;
    ch[x][!k] = y; f[y] = x;
    pushup(y); pushup(x);
}
inline void splay(int x, int g) {
    while(f[x] != g) {
        int y = f[x], z = f[y];
        if(z != g) get(x) ^ get(y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if(!g) root = x;
}
//---------------------------------------------------------
inline void insert(int v)
{
    int x = root, ff = 0;
    while(x && val[x] != v) ff = x, x = ch[x][v > val[x]];
    if(x) cnt[x]++;
    else {
        x = ++sz;
        if(ff) ch[ff][x > val[ff]] = x;
        f[x] = ff; val[x] = v; cnt[x] = 1; siz[x] = 1;
    }
}
inline void find(int v)
{
    int x = root;
    if(!x) return;
    while(ch[x][v > val[x]] && v != val[x])
        x = ch[x][v > val[x]];
    splay(x, 0);
}
inline int Next(int v, int p)
{
    find(v);
    int x = root;
    if(val[x] > v && p) return x;
    if(val[x] < v && !p) return x;
    x = ch[x][p];
    while(ch[x][p ^ 1]) x = ch[x][p ^ 1];
    return x;
}
inline void Delete(int v)
{
    int last = Next(v, 0), nxt = Next(v, 1);
    splay(last, 0); splay(nxt, last);
    int x = ch[nxt][0];
    if(cnt[x] > 1) cnt[x]--, splay(x, 0);
    else ch[nxt][0] = 0;
}
inline int Kth(int k)
{
	int x = root;
    if(siz[x] < k) return 0;
	while(true) {
		if(k <= siz[ch[x][0]]) x = ch[x][0];
		else {
			k -= siz[ch[x][0]] + 1;
			if(!k) return x;
			x = ch[x][1];
		}
	}
    
}