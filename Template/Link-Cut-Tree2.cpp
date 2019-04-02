#include <cstdio>
#include <iostream>

using namespace std;
const int N = 100005;

struct LCT
{
    #define ls ch[x][0]
    #define rs ch[x][1]
    int ch[N][2], f[N], rev[N], sum[N], w[N];
    inline int get(int x) { return ch[f[x]][1] == x; }
    inline int isr(int x) { return ch[f[x]][0] != x && ch[f[x]][1] != x; }
    inline void pushup(int x) { sum[x] = sum[ls] ^ sum[rs] ^ w[x]; }
    inline void pushr(int x) { rev[x] ^= 1; swap(ls, rs); }
    inline void pushdown(int x) {
        if(rev[x]) {
            if(ls) pushr(ls);
            if(rs) pushr(rs);
            rev[x] ^= 1;
        }
    }
    void pd(int x) { if(!isr(x)) pd(f[x]); pushdown(x); }
    inline void rotate(int x) {
        int y = f[x], z = f[y], k = get(x);
        if(!isr(y)) ch[z][get(y)] = x; f[x] = z;
        ch[y][k] = ch[x][!k]; f[ch[y][k]] = y;
        ch[x][!k] = y; f[y] = x;
        pushup(y); pushup(x);
    }
    inline void splay(int x) {
        pd(x);
        for(; !isr(x); rotate(x))
            if(!isr(f[x])) rotate(get(x) ^ get(f[x]) ? x : f[x]);
    }
    inline void access(int x) {
        for(int y = 0; x; y = x, x = f[x]) splay(x), rs = y, pushup(x);
    }
    inline void makeroot(int x) {
        access(x); splay(x); pushr(x);
    }
    inline int findroot(int x) {
        access(x); splay(x);
        while(ls) pushdown(x), x = ls;
        splay(x);
        return x;
    }
    inline int link(int x, int y) {
        makeroot(x);
        if(findroot(y) != x) f[x] = y;
    }
    inline void split(int x, int y) {
        makeroot(x); access(y); splay(y);
    }
    inline void Tcut(int x, int y) {
        split(x, y);
        f[x] = ch[y][0] = 0; pushup(y);
    }
    inline void cut(int x, int y) {
        makeroot(x);
        if(findroot(y) != x || f[y] != x || ch[y][0]) return;
        f[y] = ch[x][1] = 0;
        pushup(x);
    }
}lct;
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &lct.w[i]);
    int opt, x, y;
    while(q--)
    {
        scanf("%d%d%d", &opt, &x, &y);
        if(opt == 0) lct.split(x, y), printf("%d\n", lct.sum[y]);
        if(opt == 1) if(lct.findroot(x) != lct.findroot(y)) lct.link(x, y);
        if(opt == 2) lct.cut(x, y);
        if(opt == 3) lct.w[x] = y, lct.splay(x);
    }
    return 0;
}