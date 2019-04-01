#include <iostream>
#include <cstdio>
#include <cstdlib>
#define ll long long

using namespace std;
const int N = 1000005, inf = 1e9;
int n;
int ch[N][2];
int val[N],dat[N];
int size[N],cnt[N];
int tot,root;
int New(int _val) {
    val[++tot] = _val;
    dat[tot] = rand();
    size[tot] = 1;
    cnt[tot] = 1;
    return tot;
}
void pushup(int id) {
    size[id] = size[ch[id][0]] + size[ch[id][1]] + cnt[id];
}
void build() {
    root = New(-inf), ch[root][1] = New(inf);
    pushup(root);
}
void Rotate(int &id, int d) {
    int temp = ch[id][d ^ 1];
    ch[id][d ^ 1] = ch[temp][d];
    ch[temp][d] = id;
    id = temp;
    pushup(ch[id][d]), pushup(id);
}
void insert(int &id, int v) {
    if(!id) { id = New(v); return; }
    if(v == val[id]) cnt[id]++;
    else {
        int d = v < val[id] ? 0 : 1;
        insert(ch[id][d], v);
        if(dat[id] < dat[ch[id][d]]) Rotate(id, d ^ 1);
    } pushup(id);
}
void Remove(int &id, int v) {
    if(!id) return;
    if(v == val[id]) {
        if(cnt[id] > 1) { cnt[id]--; pushup(id); return; }
        if(ch[id][0] || ch[id][1]) {
            if(!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]])
                Rotate(id, 1), Remove(ch[id][1], v);
            else Rotate(id, 0), Remove(ch[id][0], v);
            pushup(id);
        } else id = 0; return;
    }
    v < val[id] ? Remove(ch[id][0], v) : Remove(ch[id][1], v);
    pushup(id);
}
int get_rank(int id, int v) {
    if(!id) return 0;
    if(v == val[id]) return size[ch[id][0]] + 1;
    else if(v < val[id]) return get_rank(ch[id][0], v);
    else return size[ch[id][0]] + cnt[id] + get_rank(ch[id][1], v);
}
int get_val(int id, int rank) {
    if(!id) return inf;
    if(rank <= size[ch[id][0]]) return get_val(ch[id][0], rank);
        else if(rank <= size[ch[id][0]] + cnt[id]) return val[id];
    else return get_val(ch[id][1], rank - size[ch[id][0]] - cnt[id]);
}
int get_pre(int v) {
    int id = root, pre;
    while(id) {
        if(val[id] < v) pre = val[id], id = ch[id][1];
        else id = ch[id][0];
    } return pre;
}
int get_next(int v) {
    int id = root, nxt;
    while(id) {
        if(val[id] > v) nxt = val[id], id = ch[id][0];
        else id = ch[id][1];
    } return nxt;
}
int main()
{
    build();
    scanf("%d", &n);
    for(int i = 1, op, x; i <= n; i++)
    {
        scanf("%d%d", &op, &x);
        if(op == 1) insert(root, x);
        else if(op == 2) Remove(root, x);
        else if(op == 3) printf("%d\n", get_rank(root, x) - 1);
        else if(op == 4) printf("%d\n", get_val(root, x + 1));
        else if(op == 5) printf("%d\n", get_pre(x));
        else if(op == 6) printf("%d\n", get_next(x));
    }
    return 0;
}