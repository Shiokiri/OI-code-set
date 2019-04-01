#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const double eps = 1e-7;
int n;
double a[105][105];
double ans[105];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n + 1; ++j)
            scanf("%lf", &a[i][j]);
    for(int i = 1; i <= n; ++i) {
        int r = i;
        for(int j = i + 1; j <= n; ++j)
            if(fabs(a[r][i]) < fabs(a[j][i]))
                r = j;
        if(fabs(a[r][i]) < eps) {
            printf("No Solution");
            return 0;
        }
        if(i != r) swap(a[i], a[r]);
        double div = a[i][i];
        for(int j = i; j <= n + 1; ++j)
            a[i][j] /= div;
        for(int j = i + 1; j <= n; ++j) {
            div = a[j][i];
            for(int k = i; k <= n + 1; ++k)
                a[j][k] -= a[i][k] * div;
        }
    }
    ans[n] = a[n][n + 1];
    for(int i = n - 1; i >= 1; --i) {
        ans[i] = a[i][n + 1];
        for(int j = i + 1; j <= n; ++j)
            ans[i] -= a[i][j] * ans[j];
    }
    for(int i = 1; i <= n; ++i)
        printf("%.2lf\n", ans[i]);
    return 0;
}