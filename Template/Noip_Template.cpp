1.图论
//SPFA
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int N = 10005, M = 500005;
int n,m,s;
struct Edge {
    int Next,to,dis;
}e[M*2];
int head[N],num;
void add(int from,int to,int dis)
{
    e[++num].Next = head[from];
    e[num].to = to;
    e[num].dis = dis;
    head[from] = num;
}
int dist[N],vis[N];
queue<int> q;
void spfa(int x)
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[x] = 0; vis[x] = 1;
    q.push(x);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i; i = e[i].Next)
        {
            int v = e[i].to;
            if(dist[v] > dist[u] + e[i].dis)
            {
                dist[v] = dist[u] + e[i].dis;
                if(!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
}
//dijkstra
#include <iostream>
#include <cstdio>
#include <queue>
const int maxn = 500005;
const int inf = 0x3f3f3f3f;
int n,m,s;
struct Edge {
    int next,to,dis;
}e[maxn];
int head[maxn],num;
void add(int from,int to,int dis)
{
    e[++num].next = head[from];
    e[num].to = to;
    e[num].dis = dis;
    head[from] = num;
}
int dist[maxn],vis[maxn];
struct node {
    int u,dis;
    bool operator < (const node rhs) const {
        return dis > rhs.dis;
    }
};
std::priority_queue<node> q;
void dijkstra(int x)
{
    for(int i=1; i<=n; i++) dist[i] = inf;
    dist[x] = 0;
    q.push((node){x,0});
    while(!q.empty())
    {
        node fr = q.top(); q.pop();
        int u = fr.u;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i=head[u]; i; i=e[i].next)
        {
            int v = e[i].to;
            if(dist[v] > dist[u] + e[i].dis)
            {
                dist[v] = dist[u] + e[i].dis;
                if(!vis[v]) q.push((node){v,dist[v]});
            }
        }
    }
}
//floyd
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(dis[i][j]>dis[i][k]+dis[k][j])
                dis[i][j]=dis[i][k]+dis[k][j];

//最短路计数
1.if(dis[v] > dis[u] + e[i].dis)		cnt[v] = cnt[u];
2.if(dis[v] == dis[u] + e[i].dis)	cnt[v] = (cnt[v] + cnt[u]) % mod;
//并查集
int father[N];
for(int i=1;i<=n;i++)	  father[i]=i;
int find(int x)
{
    if(father[x]!=x) father[x]=find(father[x]);
    return father[x];
}
void uni(int x,int y)
{
    x=find(x);y=find(y);
    father[y]=x;
}
//kruskal
struct edge {
    int u,v,z;
}e[N];
bool cmp(edge a,edge b) {
    return a.z < b.z;
}
sort(e+1,e+m+1, cmp);
for(int i=1;i<=m;i++)
{
    if(find(e[i].x)!=find(e[i].y))
    {
        uni(e[i].x,e[i].y);
        cnt++;
        sum+=e[i].z;
    }
    if(cnt == n-1)
        break;
}
// 倍增lca
#include <iostream>
#include <cstdio>

using namespace std;
const int N = 500000 + 5;
int n,m,root;
struct Edge {
    int Next,to;
}e[N*2];
int head[N],num;
void add(int from,int to)
{
    e[++num].Next = head[from];
    e[num].to = to;
    head[from] = num;
}
int p[N][21],deep[N];
void dfs(int u,int father)
{
    deep[u] = deep[father] + 1;
    p[u][0] = father;
    for(int i=1; (1<<i) <= deep[u]; i++)
        p[u][i] = p[p[u][i-1]][i-1];
    for(int i=head[u]; i; i=e[i].Next)
        if(e[i].to != father)
            dfs(e[i].to,u);
}
int lca(int x,int y)
{
    if(deep[x] > deep[y])
        swap(x,y);
    for(int i=20; i>=0; i--)
        if(deep[y] - (1<<i) >= deep[x])
            y = p[y][i];
    if(x == y) return x;
    for(int i=20; i>=0; i--)
        if(p[x][i] != p[y][i])
            x=p[x][i],y=p[y][i];
    return p[x][0];
}
//tarjan
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;
const int N = 10005, M = 50005;
int n,m;
struct Edge {
    int Next,to;
}e[M];
int head[N],num;
void add(int from,int to) {
    e[++num].Next = head[from]; e[num].to = to; head[from] = num;
}
int dfn[N],low[N],vis[N],color[N],deep,sum;
stack<int> s;
void tarjan(int u)
{
    dfn[u] = low[u] = ++deep;
    vis[u] = 1;
    s.push(u);
    for(int i=head[u]; i; i=e[i].Next)
    {
        int v = e[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(vis[v]) low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        color[u] = ++sum;
        vis[u] = 0;
        while(s.top() != u)
        {
            color[s.top()] = sum;
            vis[s.top()] = 0; s.pop();
        }
        s.pop();
    }
}
int main()
{
    for(int i=1; i<=n; i++)
        if(!dfn[i])
            tarjan(i);
}
2.数据结构
//单调队列
f[i]=max/min{f[j](j∈g(i))}+a[i]
dp[i]=max(dp[k]) (k∈[i+l,i+r]) +a[i]
#include<cstdio>
const int maxn = 2*1e6+10;
int n,k,a[maxn],q[maxn],head=1,tail=0;
int main() {
    scanf("%d%d%d",&n,&k,&a[1]);
    q[++tail]= 1;
    for(int i=2;i<=n;i++) {
        scanf("%d",&a[i]);
        while(head<=tail&&a[i]>a[q[tail]]) tail--;
        q[++tail]=i;
        if(i-q[head]==k) head++;
        if(i>=k) printf("%d\n",a[q[head]]);
    }
    return 0;
}
17pjt4
#include<iostream>
#include<cstdio>
#include<cstring>
#define re register
#define F(a,b) for(re int i=a;i<=b;i++)
using namespace std;
const int inf =1e9;
const int maxn=500000+10;
int n,d,k;
int dis[maxn],s[maxn],f[maxn],q[maxn];
inline bool dp(int g) {
    int p=0,h=1,t=0 ;q[h]=0;	F(1,n) f[i]=-inf;
    F(1,n) {
        while( dis[i]-dis[p] >= max(d-g,1) && p<i ) {
            while( f[q[t]]<=f[p] && h<=t ) t--;
            q[++t] = p++;
        }
        while( dis[i]-dis[q[h]] > d+g && h<=t ) h++;
        if( h>t || f[q[h]]==-inf ) continue;
        else f[i] = f[q[h]] + s[i];
        if( f[i] >= k ) return true;
    }
    return false;
}
int main() {
    scanf("%d%d%d",&n,&d,&k);
    F(1,n) scanf("%d%d",&dis[i],&s[i]);
    int l=1, r=dis[n]+10, ans=0;
    if( dp(r) == 0 ) {
        printf("-1\n"); return 0;
    }
    while(l<=r) {
        int mid= (l+r) >> 1;
        if( dp(mid) ) r=mid-1, ans=mid;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
//ST表
#include<iostream>
#include<cstdio>
#define re register
using namespace std;
int n,m,l,r,dp[100005][30];
inline int RMQ(int L,int R){
    int k=0,T=R-L+1;
    while((1<<(k+1)) <= T) k++;
    return max(dp[L][k],dp[R-(1<<k)+1][k]);
}
int main(){
    scanf("%d%d",&n,&m);
    for(re int i=1;i<=n;i++) scanf("%d",&dp[i][0]);
    for(re int j=1;(1<<j)<=n;j++)
        for(re int i=1;i+(1<<j)-1<=n;i++)
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
    for(re int i=1;i<=m;i++){
        scanf("%d%d",&l,&r);
        printf("%d\n",RMQ(l,r));
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int f[100005][21],a[100005];
void ST()
{
	int k=log(n)/log(2);
	for(int i=1; i<=n; i++) f[i][0]=a[i];
	for(int j=1; j<=k; j++)
		for(int i=1; i+(1<<j)-1 <=n; i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
int RMQ(int L,int R)
{
	int k=log(R-L+1)/log(2);
	return max(f[L][k],f[R-(1<<k)+1][k]);
}
//树状数组
单点修改，区间查询
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int C[500010];
int order,x,y;
inline int lowbit(int x) {
    return x&(-x);
}
inline void add(int x,int k) {
    for(int i=x;i<=n;i+=lowbit(i))
        C[i]+=k;
}
inline int sum(int x) {
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i))
        ans+=C[i];
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        add(i,x);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&order,&x,&y);
        if(order==1){
            add(x,y);
        }
        else if(order==2){
            printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}
区间修改 单点查询 : 差分 add(a,c); add(b+1,-c);
//开放地址法hash
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 200005,p = 1000003;
long long n,c,a[N],ans;
struct node { long long num; int cnt; } h[p];
inline long long abs(long long x) { return x<0 ? -x : x; }
inline int hash(int x) { return x % p; }
inline int find(long long x) { int way = hash(abs(x));
    while(h[way].num && h[way].num != x) way = hash(++way); return way; }
inline void push(long long x) { int way = find(x); h[way].cnt ++; h[way].num = x; }
inline int check(long long x) { return h[find(x)].cnt; }
int main()
{
    scanf("%lld%lld", &n, &c);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), push(a[i]);
    for(int i = 1; i <= n; i++) ans += check(a[i] + c);
    printf("%lld", ans);
    return 0;
}
//字符串hash
typedef long long ll;
typedef unsigned long long ull;
const int base=233,N=10000+5;
ll f[N],n;string s;
ull hash(string str) {
    ull ans=0,len=str.length();
    for(ll i=0;i<len;i++) 
        ans=ans*base+(ull)str[i];
    return ans;
}
//邻接表
struct Edge {
    int Next,to,dis;
}e[M*2];
int head[N],num;
void add(int from,int to,int dis)
{
    e[++num].Next = head[from];
    e[num].to = to;
    e[num].dis = dis;
    head[from] = num;
}
//线段树传参写法
#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 400010
#define ll long long
#define re register
#define FOR(i, l, r) for(re ll i = l; i <= r; ++i)
using namespace std;
ll n, m, c, r, t, x, y, z;
ll a[maxn], ans[maxn], tag[maxn];
inline ll ls(ll k) { return k << 1; }
inline ll rs(ll k) { return k << 1 | 1; }
inline void push_up(ll p) { 
	ans[p] = ans[ls(p)] + ans[rs(p)]; 
}
inline void ff(ll p, ll l, ll r, ll k) {
	ans[p] += (r-l+1) * k;
	tag[p] += k;
}
inline void push_down(ll p, ll l, ll r) {
	ll mid = (l+r) >> 1;
	ff(ls(p), l, mid, tag[p]);
	ff(rs(p), mid+1, r, tag[p]);
	tag[p] = 0;
}
void build(ll p, ll l, ll r) {
	if(l == r) {
		ans[p] = a[l];
		return;
	}
	ll mid = (l+r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid+1, r);
	push_up(p);
}
void update(ll nl, ll nr, ll l, ll r, ll p, ll k) {
	if(nl <= l && r <= nr) {
		ans[p] += (r-l+1) * k;
		tag[p] += k;
		return;
	}
	push_down(p, l, r);
	ll mid = (l+r) >> 1;
	if(nl <= mid)
	  update(nl, nr, l, mid, ls(p), k);
	if(nr > mid)
	  update(nl, nr, mid+1, r, rs(p), k);
	push_up(p);
}
ll query(ll q_x, ll q_y, ll l, ll r, ll p) {
	if(q_x <= l && r <= q_y)
	  return ans[p];
	push_down(p, l, r);
	ll res = 0;
	ll mid = (l+r) >> 1;
	if(q_x <= mid)
	  res += query(q_x, q_y, l, mid, ls(p));
	if(q_y > mid)
	  res += query(q_x, q_y, mid+1, r, rs(p));
	return res;
}
int main() {
	scanf("%lld%lld", &n, &m);
	FOR(i, 1, n)
	  scanf("%lld", &a[i]);
	build(1, 1, n);
	FOR(i, 1, m) {
		scanf("%lld", &t);
		if(t == 1) {
			scanf("%lld%lld%lld", &x, &y, &z);
			update(x, y, 1, n, 1, z);
		}
		else {
			scanf("%lld%lld", &x, &y);
			printf("%lld\n", query(x, y, 1, n, 1));
		}
	}
}
//线段树结构体写法
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=100000+10;
ll n,p,a,b,m,x,y,ans;
struct node{
    ll l,r,w,f;
}tree[maxn*4];
void build(ll k,ll l,ll r){
    tree[k].l=l,tree[k].r=r;
    if(tree[k].l==tree[k].r){
        scanf("%lld",&tree[k].w);return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree[k].w=tree[k<<1].w+tree[k<<1|1].w;
}
inline void down(ll k){
    tree[k<<1].f+=tree[k].f;
    tree[k<<1|1].f+=tree[k].f;
    tree[k<<1].w+=tree[k].f*(tree[k<<1].r-tree[k<<1].l+1);
    tree[k<<1|1].w+=tree[k].f*(tree[k<<1|1].r-tree[k<<1|1].l+1);
    tree[k].f=0;
}
void ask_point(ll k){
    if(tree[k].l==tree[k].r){
        ans=tree[k].w;return;
    }
    if(tree[k].f) down(k);
    int mid=(tree[k].l+tree[k].r)>>1;
    if(x<=mid) ask_point(k<<1);
    else ask_point(k<<1|1);
}
void change_point(ll k){
    if(tree[k].l==tree[k].r){
        tree[k].w+=y;return;
    }
    if(tree[k].f) down(k);
    int mid=(tree[k].l+tree[k].r)>>1;
    if(x<=mid) change_point(k<<1);
    else change_point(k<<1|1);
    tree[k].w=tree[k<<1].w+tree[k<<1|1].w;
}
void ask_interval(ll k){
    if(tree[k].l>=a&&tree[k].r<=b){
        ans+=tree[k].w;return;
    }
    if(tree[k].f) down(k);
    int mid=(tree[k].l+tree[k].r)>>1;
    if(a<=mid) ask_interval(k<<1);
    if(b>mid) ask_interval(k<<1|1);
}
void change_interval(ll k){
    if(tree[k].l>=a&&tree[k].r<=b){
        tree[k].w+=(tree[k].r-tree[k].l+1)*y;
        tree[k].f+=y;return;
    }
    if(tree[k].f) down(k);
    int mid=(tree[k].l+tree[k].r)>>1;
    if(a<=mid) change_interval(k<<1);
    if(b>mid) change_interval(k<<1|1);
    tree[k].w=tree[k<<1].w+tree[k<<1|1].w;
}
int main(){
    scanf("%lld%lld",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;i++){
        scanf("%lld",&p);
        ans=0;
        if(p==1){
            scanf("%lld%lld%lld",&a,&b,&y);
            change_interval(1);
        }
        else if(p==2){
            scanf("%lld%lld",&a,&b);
            ask_interval(1);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
3.数论
//快速幂
ll quickpow(ll x, ll y, ll mod){ ll res = 1; 
	while(y) { if(y & 1) res = (res * x) % mod; x = (x * x) % mod; y >>= 1; }
	return res;
}
//欧几里得
ll gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }
ll ex_gcd(int a, int b, int &x, int &y) {
	if (b == 0) { x = 1; y = 0; return a;}
	ll g = ex_gcd(b,a%b,y,x); y -= a/b*x; return g;
}
//乘法逆元
ll inv[maxn];
void _inv(ll p, ll n) { inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = 1LL*(p-p/i)*inv[p%i]%p;
}
//素数埃筛 nlogn
int prime[maxn];
void _prime(ll n) { prime[1]=1;
	for(int i = 2;i <= n; i++)
		if(prime[i] == 0)
			for(int j = 2;i * j <= n; j++)
				prime[i * j] = 1;
}
//计算系数_(ax+by)^k x^n y^m时的系数
int main() {
    scanf("%d%d%d%d%d",&a,&b,&k,&n,&m);
    int ans=1;
    ans=ans*p(a%mod,n)%mod*p(b%mod,m)%mod;
    C[1][0]=1;C[1][1]=1;// 组合数递推
    for(int i=2;i<=k;i++) {
        C[i][0]=1;
        for(int j=1;j<=n;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    ans=(ans*C[k][n])%mod;
    printf("%d\n",ans);
    return 0;
}

4.搜索模拟其它
void dfs(int cur,...) //其他参数 
{
	if(剪枝) ... //可行性剪枝 最优性剪枝 
	...
	if(cur到达目标)
	{
		if(答案 == true)
			print();//输出 
		return;
	}
	for(int i = 1; i <= n; i++) //向下可能的分枝
		if(满足条件)
	{
		...//存状态 
		dfs(cur+1,...);
		...//回溯状态 
	}
}
void bfs()
{
	head = 0, tail = 1; 		 |  while(!q.empty()) q.pop();
	q[1].x = .., q[1].y = ..;    |  q.push((node){..,..});
	while(head < tail)  		 |  while(!q.empty())
	{
		head++;	int .. = q[head].x;	 | node fr = q.front(); q.pop(); int .. = fr.x;
		for(int i = 1; i <= n; i++) //分枝
			if(满足条件 && vis[][] == 0) //一定状态 
		{
			vis[][] = 1; //存储状态
			q[++tail].x = ...;   |  q.push((node){..,..});
			q[tail].y = ...; 
		}
	}
}
//迭代加深 （埃及分数）
#include<iostream>
#include<cstdio>
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
ll a,b;
ll deep,best=inf;
ll now[10005],ans[10005];
bool flag=1;
ll gcd(ll a,ll b){
	return b == 0 ? a : gcd(b,a%b);
}
void dfs(ll t,ll a,ll b,ll last){
	ll l=max(last+1,b/a),r=min((deep+1-t)*b/a,best-1); //上下界
	for(ll i=l;i<=r;i++)
	{
		now[t]=i;
		ll x=a*i-b;
		ll y=b*i;
		if(x<0) continue;
		if(t<deep) dfs(t+1,x,y,i);
		if(t==deep){
			if(i<best&&x==0){
				best=i,flag=0;
				for(ll j=1;j<=deep;j++)
					ans[j]=now[j];
			}
			return;
		}
	}
}
int main(){
	cin>>a>>b;
	while(flag){
		deep++;
		dfs(1,a,b,1);
	}
	for(ll i=1;i<=deep;i++)
		cout<<ans[i]<<" ";
	return 0;
}
//高精度
const int MAXN = 105;
struct bign  
{  
    int len, s[MAXN];
    bign ()  //初始化
    {  
        memset(s, 0, sizeof(s));  
        len = 1;  
    }  
    bign (int num) { *this = num; }  
    bign (const char *num) { *this = num; }  //让this指针指向当前字符串
    bign operator = (const int num)
    {  
        char s[MAXN];
        sprintf(s, "%d", num);  //sprintf函数将整型映到字符串中
        *this = s;
        return *this;  //再将字符串转到下面字符串转化的函数中
    }  
    bign operator = (const char *num)  
    {  
        for(int i = 0; num[i] == '0'; num++) ;  //去前导0  
        len = strlen(num);  
        for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0'; //反着存
        return *this;
    }  
    bign operator + (const bign &b) const //对应位相加，最为简单
    {  
        bign c;  
        c.len = 0;  
        for(int i = 0, g = 0; g || i < max(len, b.len); i++)  
        {  
            int x = g;  
            if(i < len) x += s[i];  
            if(i < b.len) x += b.s[i];  
            c.s[c.len++] = x % 10;  //关于加法进位
            g = x / 10;  
        }  
        return c;  
    }  
    bign operator += (const bign &b)  //如上文所说，此类运算符皆如此重载
    {  
        *this = *this + b;  
        return *this;  
    }  
    void clean()  //由于接下来的运算不能确定结果的长度，先大而估之然后再查
    {  
        while(len > 1 && !s[len-1]) len--;  //首位部分‘0’故删除该部分长度
    }   
    bign operator * (const bign &b) //乘法重载在于列竖式，再将竖式中的数转为抽象，即可看出运算法则。
    {  
        bign c;  
        c.len = len + b.len;  
        for(int i = 0; i < len; i++)  
        {  
            for(int j = 0; j < b.len; j++)  
            {  
                c.s[i+j] += s[i] * b.s[j];//不妨列个竖式看一看
            }  
        }  
        for(int i = 0; i < c.len; i++) //关于进位，与加法意同 
        {  
            c.s[i+1] += c.s[i]/10;
            c.s[i] %= 10;
        }  
        c.clean();  //我们估的位数是a+b的长度和，但可能比它小（1*1 = 1）
        return c;  
    }  
    bign operator *= (const bign &b)  
    {  
        *this = *this * b;  
        return *this;  
    }  
    bign operator - (const bign &b)  //对应位相减，加法的进位改为借1
    {  //不考虑负数
        bign c;  
        c.len = 0;  
        for(int i = 0, g = 0; i < len; i++)  
        {  
            int x = s[i] - g;  
            if(i < b.len) x -= b.s[i];  //可能长度不等
            if(x >= 0) g = 0;  //是否向上移位借1
            else  
            {  
                g = 1;  
                x += 10;  
            }  
            c.s[c.len++] = x;  
        }  
        c.clean();  
        return c;   
    }  
    bign operator -= (const bign &b)  
    {  
        *this = *this - b;  
        return *this;  
    }  
    bign operator / (const bign &b)  //运用除是减的本质，不停地减，直到小于被减数
    {  
        bign c, f = 0; //可能会在使用减法时出现高精度运算 
        for(int i = len-1; i >= 0; i--)  //正常顺序，从最高位开始
        {  
            f = f*10;  //上面位的剩余到下一位*10
            f.s[0] = s[i];  //加上当前位
            while(f >= b)  
            {  
                f -= b;  
                c.s[i]++;  
            }  
        }  
        c.len = len;  //估最长位
        c.clean();  
        return c;  
    }  
    bign operator /= (const bign &b)  
    {  
        *this  = *this / b;  
        return *this;  
    }  
    bign operator % (const bign &b)  //取模就是除完剩下的
    {  
        bign r = *this / b;  
        r = *this - r*b;  
        r.clean();
        return r;  
    }  
    bign operator %= (const bign &b)  
    {  
        *this = *this % b;  
        return *this;  
    }  
    bool operator < (const bign &b) //字符串比较原理 
    {  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] < b.s[i];  
        }  
        return false;  
    }  
    bool operator > (const bign &b)  //同理
    {  
        if(len != b.len) return len > b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] > b.s[i];  
        }  
        return false;  
    }  
    bool operator == (const bign &b)  
    {  
        return !(*this > b) && !(*this < b);  
    }  
    bool operator != (const bign &b)  
    {  
        return !(*this == b);  
    }  
    bool operator <= (const bign &b)  
    {  
        return *this < b || *this == b;  
    }  
    bool operator >= (const bign &b)  
    {  
        return *this > b || *this == b;  
    }  
    string str() const  //将结果转化为字符串（用于输出）
    {  
        string res = "";  
        for(int i = 0; i < len; i++) res = char(s[i]+'0')+res;  
        return res;  
    }  
};
istream& operator >> (istream &in, bign &x) //重载输入流 
{  
    string s;  
    in >> s;  
    x = s.c_str();  //string转化为char[]
    return in;
}  
ostream& operator << (ostream &out, const bign &x)  //重载输出流
{  
    out << x.str();
    return out;  
}
//树上背包
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int inf = 1e9;
const int maxn = 10005;
int n,m;
int w[maxn];
struct Edge {
    int _next,to,dis;
}e[maxn];
int head[maxn],num;
void add(int from,int to,int dis)
{
    e[++num]._next = head[from];
    e[num].to = to;
    e[num].dis = dis;
    head[from] = num;
}
int dp[3005][3005];
int dfs(int u)
{
    if (u >= n - m + 1)
    {
        dp[u][1] = w[u];
        return 1;
    }
    int sum = 0 , t = 0;
    for(int i = head[u]; i; i=e[i]._next)//阶段 已经跑到第几个son了  -阶段- 
    {//第一维滚动压掉  下面一行i表示第几次进入循环即跑到第几个儿子了
    // f[i][u][k] = max(dp[i][u][k] , dp[i-1][u][j-k] + dp[son_num(v)][v][k] - dis u->v )
        int v = e[i].to;//son 
        t = dfs(v); sum += t;//u结点能连到的用户数 
    //  v/son 结点能连到的用户数 
        for(int j = sum; j >= 1; j--) //当前节点选几个用户跑一边   -状态-
            for(int k = 1; k <= t; k++) //分组 子节点选1-t个用户 只能选其中一种结果  -分组-
                if(j - k >= 0) //         倒序 用到了j-k之前的状态(i-1次的)
                    dp[u][j] = max(dp[u][j] , dp[u][j-k] + dp[v][k] - e[i].dis);//每次跑k - j只转移其中一种 
//              u结点选j个用户 max    自己   u点选j-k个用户 son点选k个用户 u->v的花费
    }
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=1, k,v,z; i<=n-m; i++)
    {
        scanf("%d", &k);
        for(int j=1; j<=k; j++)
        {
            scanf("%d%d", &v, &z);
            add(i,v,z);
        }
    }
    for(int i=n-m+1; i<=n; i++)
        scanf("%d", &w[i]);
    for(int i=1 ;i<=n; i++)
        for(int j=1 ;j<=n; j++)
            dp[i][j] = -inf;
    for(int i=1; i<=n; i++) dp[i][0] = 0;//选0个花费0 
    dfs(1);
    for(int i=m; i>=1; i--)
        if(dp[1][i] >= 0) // 选i个剩下0元以上 
    {
        printf("%d\n", i);
        break;
    }
    return 0;
}
//01背包
for i=1..N
    for v=V..0
        f[v]=max{f[v],f[v-c[i]]+w[i]}
//完全背包
for i=1..N
    for v=0..V
        f[v]=max{f[v],f[v-cost]+weight}
// 二维费用
f[i][v][u]=max{f[i-1][v][u],f[i-1][v-a[i]][u-b[i]]+w[i]}
//分组背包
for 所有的组k
    for v=V..0
        for 所有的i属于组k
            f[v]=max{f[v],f[v-c[i]]+w[i]}
//多重背包 O(V*Σn[i])
f[i][v]=max{f[i-1][v-k*c[i]]+k*w[i]|0<=k<=n[i]}
//矩阵取数
for(int i = 1; i <= m; i++)
     f[i][i] = a[i] * p[m];
        for(int l = 2; l <= m; l++)
            for(int i = 1; (i+l-1) <= m; i++)
 {
        int j = i + l -1;
        f[i][j] = max(f[i+1][j] + a[i] * p[m-l+1] , f[i][j-1] + a[j] * p[m-l+1]);
 }
//乘积最大
for(int i = 2; i <= n; i++)
        for(int j = i - 1; j >= 1; j--)
            a[j][i] = a[j][i-1] * 10 + a[i][i];
    for(int i = 1; i <= n; i++)
        f[i][0] = a[1][i];
    for(int k = 1; k <= _k; k++)
        for(int i = k + 1; i <= n; i++)
            for(int j = k; j < i; j++)
            	if(f[i][k] < f[j][k-1] * a[j+1][i])
            		f[i][k] = f[j][k-1] * a[j+1][i];
//树上差分
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define re register

using namespace std;
const int maxn=300000+5;

int n,m,log_max,root;
//edge
struct Edge {
    int next,to,dis;
}e[maxn*2];
int head[maxn],num;
inline void add(int from,int to,int dis)
{
    e[++num].next = head[from];
    e[num].to = to;
    e[num].dis = dis;
    head[from] = num;
}
struct m_plan {
    int from,to,lca,len;
}plan[maxn];

//read
inline int read() 
{
    char ch;
    while (ch = getchar(), ch < '0' || ch > '9');
    int res = ch - 48;
    while (ch = getchar(), ch >= '0' && ch <= '9') res = res * 10 + ch - 48;
    return res;
}

//tree LCA
int deep[maxn],p[maxn][21],pw[maxn][21];
void lca_dfs(int u)
{
    for(re int i=head[u]; i; i=e[i].next)
        if(! deep[e[i].to])
    {
        deep[e[i].to] = deep[u] + 1;
        p[e[i].to][0] = u;
        pw[e[i].to][0] = e[i].dis;
        lca_dfs(e[i].to);
    }
}
int way=0;
inline int lca(int x,int y)
{
    way=0;
    if(deep[x] < deep[y])
        swap(x,y);
    for(re int i=log_max; i>=0; i--)
        if(deep[ p[x][i] ] >= deep[y])
            way = way + pw[x][i] , x = p[x][i];
    if(x == y) return x;
    for(re int i=log_max; i>=0; i--)
        if(p[y][i] != p[x][i])
    {
        way = way + pw[x][i] + pw[y][i];
        x=p[x][i] , y=p[y][i];
    }
    way = way + pw[x][0] + pw[y][0];
    return p[x][0];
}

//tree diff
int diff[maxn];
int MaxPublic,tot;
void _public(register int u)
{
    for(re int i=head[u]; i; i=e[i].next)
        if(e[i].to != p[u][0])
    {
        _public(e[i].to);
        diff[u] += diff[e[i].to];
    }
    if(diff[u] == tot)
        MaxPublic = max(MaxPublic , pw[u][0]);
}
inline bool check(int tim)
{
    tot=0;
    memset(diff,0,sizeof(diff));
    int MaxDis = -1; MaxPublic = -1;
    for(re int i=1; i<=m; i++)
        if(plan[i].len > tim)
    {
        tot++;
        diff[plan[i].from] ++; diff[plan[i].to] ++;
        diff[plan[i].lca] -= 2;
        MaxDis = max(MaxDis , plan[i].len);
    }
    if(tot == 0) return true;
    _public(root);
    if(MaxDis - MaxPublic <= tim)
        return true;
    else
        return false;
}

int main()
{
    n=read(); m=read();
    log_max = (int)log2(n);
    root = max(1 , n>>4);
    int Max1 = -1 , Maxr = -1;
    for(re int i=1,u,v,z; i<=n-1; i++)
    {
        u=read(); v=read(); z=read();
        add(u,v,z); add(v,u,z);
        Max1 = max(Max1 , z);
    }
    deep[root] = 1;
    lca_dfs(root);
    for(re int j=1; j<=log_max; j++)
        for(re int i=1; i<=n; i++)
    {
        p[i][j] = p[ p[i][j-1] ][j-1] ;
        pw[i][j] = pw[i][j-1] + pw[ p[i][j-1] ][j-1];
    }
    for(re int i=1; i<=m; i++)
    {
        plan[i].from = read(); plan[i].to = read();
    }
    for(re int i=1; i<=m; i++)
    {
        plan[i].lca = lca(plan[i].from , plan[i].to);
        plan[i].len = way;
        Maxr = max(Maxr , way);
    }
    int l = Maxr - Max1, r = Maxr + 1, mid, ans = 0;
    while(l <= r)
    {
        mid= (l + r) >> 1;
        if(check(mid)) ans = mid , r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}

//二分ans
while(l<=r)
{
    mid = (l + r) >> 1;
    if(check(mid)) 
    {
        ans = mid;
        l = mid + 1;
    }
    else r = mid -1;
}
//逆序对
#include <iostream>
#include <cstdio>

using namespace std;
int n,a[1000005],b[1000005];
long long ans;
void msort(int l,int r)
{
    if(l==r) return ;
    int mid=(l+r)>>1;
    msort(l,mid);
    msort(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j]) b[k++]=a[i++];
        else
        {
            b[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid) b[k++]=a[i++];
    while(j<=r) b[k++]=a[j++];
    for(int i=l;i<=r;i++) a[i]=b[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    msort(1,n);
    printf("%lld\n",ans);
    return 0;
}
//最短路计数
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int maxn=1000000+10;
const int mod=100003;
int n,m,x,y;
int vis[maxn],dis[maxn],ans[maxn];
vector<int> G[maxn];
queue<int> Q;
inline void SPFA(int x){
    for(int i=1;i<=n;i++) dis[i]=0x7fffffff;
    Q.push(x);vis[x]=1;dis[x]=0;ans[x]=1;
    while(!Q.empty()){
        int u=Q.front();Q.pop();vis[u]=0;
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
                ans[v]=ans[u];
                if(!vis[v]){
                    vis[v]=1;Q.push(v);
                }
            }
            else if(dis[v]==dis[u]+1)
                ans[v]=(ans[v]+ans[u])%mod;
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        G[x].push_back(y);G[y].push_back(x);
    }
    SPFA(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}