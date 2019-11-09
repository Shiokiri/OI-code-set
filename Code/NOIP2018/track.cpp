#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
int n,m;
struct bian {
	int num,id;
}l[1000005];
int B;
bool cmp1(bian x, bian y) {
	return x.id < y.id;
}
bool cmp2(int x,int y) {
	return x > y;
}
int m1[1000005],Tm;
int m2[1000005],Tm2;
struct Edge {
	int Next,to,dis;
}e[1000005];
int head[1000005],num;
void add(int from,int to,int dis)
{
	e[++num].Next = head[from];
	e[num].to = to;
	e[num].dis = dis;
	head[from] = num;
}
int dfs(int u,int father)
{
	int res = 0;
	for(int i = head[u]; i; i = e[i].Next)
		if(e[i].to != father)
	{
		res = max(res , e[i].dis + dfs(e[i].to, u));
	}
	return res;
}
bool check(int Min) {
	int tot = 0, res = 0;
	for(int i = 1; i <= B; i++)
	{
		tot += l[i].num;
		if(tot >= Min) {
			tot = 0;
			res ++;
		}
	}
	if(res >= m) return true;
	else return false;
}
int main()
{
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	scanf("%d%d", &n, &m);
	int flagai = 1,flagbi = 1,sum = 0;
	for(int i = 1,u,v,z; i < n; i++)
	{
		scanf("%d%d%d", &u, &v, &z);
		if(u != 1) flagai = 0;
		if(v != u + 1) flagbi = 0;
		l[++B].num = z; l[B].id = u;
		m1[++Tm] = z;
		sum += z;
		add(u,v,z); add(v,u,z);
	}
	if(flagbi)
	{
		sort(l+1, l+B+1, cmp1);
		int l = 0, r = sum+10, mid = 0, ans = 0;
		while(l <= r) {
			mid = (l + r) >> 1;
//			cout << l << " " << mid << " " << r << endl;
			if(check(mid)) {
				ans = mid;
				l = mid+1;
			}
			else r = mid-1;
		}
		printf("%d\n", ans);
		return 0;
	}
	else if(flagai)
	{
		sort(m1+1,m1+1+Tm);
		int l = 1, r = Tm, ans = inf;
		for(int i = 1; i <= m; i++)
		{
			ans = min(ans, m1[l] + m1[r]);
			l++; r--;
		}
		printf("%d\n", ans);
		return 0;
	}
	else if(m == 1)
	{
		for(int i = head[1]; i; i = e[i].Next)
			m2[++Tm2] = dfs(e[i].to, 1) + e[i].dis;
//		cout << m1[1] <<  " " << m1 [2] << " " << m1[3] << endl;
		sort(m2+1,m2+1+Tm2,cmp2);
		printf("%d\n", m2[1] + m2[2]);
		return 0;
	}
	return 0;
}
/*
5 1
1 2 2
1 3 3
2 4 8
2 5 7

12 1
1 2 7
1 3 11
1 4 17
2 5 11
2 6 5
2 7 6
7 8 1
7 9 2
9 10 18
3 11 5
4 12 2
*/
