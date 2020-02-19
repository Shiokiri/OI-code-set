#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;
const int N = 500005;
int n;
char a[N];
struct Edge {
	int Nxt, v;
}e[N<<1];
int h[N], p = 1;
void add(int u, int v)
{
	e[++p].Nxt = h[u];
	e[p].v = v;
	h[u] = p;
}
long long ans = 0;
char st[N]; int top;
void dfs(int u, string s)
{
	int l = s.length();
	int res = 0;
	for(int i = 0; i < l; i++)
		for(int j = i; j < l; j++)
	{
		int flag = 1;
		top = 0;
		for(int k = i; k <= j; k++)
		{
			if(s[k] == '(')
			{
				st[++top] = '(';
			}
			else if(s[k] == ')')
			{
				if(st[top] != '(' || top == 0)
				{
					flag = 0;
				}
				else if(st[top] == '(')
				{
					top--;
				}
			}
		}
		if(top != 0) flag = 0;
		res += flag;
	}
	if(ans == 0) ans = 1LL * u * res;
	else ans ^= 1LL * u * res;
	for(int i = h[u]; i; i = e[i].Nxt)
		dfs(e[i].v, s+a[e[i].v]);
}
int main()
{
	freopen("brackets.in","r",stdin);
	freopen("brackets.out","w",stdout);
	scanf("%d", &n);
	scanf("%s", a+1);
	for(int i = 2, x; i <= n; i++)
	{
		scanf("%d", &x);
		add(x, i);
	}
	string s = "";
	s += a[1];
	dfs(1, s);
	printf("%lld\n", ans);
	return 0;
}
