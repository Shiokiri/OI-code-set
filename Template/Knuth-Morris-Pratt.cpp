#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 1e6 + 5;
char a[N], b[N]; int next[N], f[N], n, m;
int main()
{
    cin >> b + 1 >> a + 1;
    n = strlen(a + 1), m = strlen(b + 1);
    for(int i = 2, j = 0; i <= n; i++) {
        while(j > 0 && a[i] != a[j + 1]) j = next[j];
        if(a[i] == a[j + 1]) j++; next[i] = j;
    }
    for(int i = 1, j = 0; i <= m; i++) {
        while(j > 0 && (j == n || b[i] != a[j + 1])) j = next[j];
        if(b[i] == a[j + 1]) j++;
        f[i] = j; if(f[i] == n) printf("%d\n", i - n + 1);
    }
    for(int i = 1; i <= n; i++) printf("%d ", next[i]);
    return 0;
}