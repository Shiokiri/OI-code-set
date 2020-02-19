#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;
const int N = 2005;
int T, n, a[N], b[N];
int x[N], y[N];
int d[N], id[N];
int ans[N], res[N];
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d", &T);
	while(T--)
	{
		memset(ans, 0x3f, sizeof(ans));
		scanf("%d", &n);
		for(int i = 1, t; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++)
		{
			scanf("%d%d", &x[i], &y[i]);
		}
		for(int i = 1; i < n; i++) id[i] = i;
		do {
			memcpy(b, a, sizeof(b));
			for(int i = 1; i < n; i++)
			{
				swap(b[x[id[i]]], b[y[id[i]]]);
			}
			for(int i = 1; i <= n; i++)
			{
				for(int j = 1; j <= n; j++)
					if(b[j] == i)
						res[i] = j;
			}
			int flag = 0;
			for(int i = 1; i <= n; i++)
				if(res[i] < ans[i])
			{
				flag = 1; break;
			}
				else if(res[i] > ans[i]) break;
			if(flag) memcpy(ans, res, sizeof(ans));
		} while(next_permutation(id+1,id+n));
		for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
