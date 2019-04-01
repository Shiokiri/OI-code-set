#include <iostream>
#include <cstdio>
#define ll long long

using namespace std;
const ll mod = 1e9 + 7;
ll T, n;
struct Mat {
    ll m[5][5];
    Mat() {
        for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++)
                m[i][j] = 0;
    }
    Mat operator * (const Mat &x) {
        Mat y;
        for(int i = 1; i <= 3; i++)
            for(int k = 1; k <= 3; k++)
                for(int j = 1; j <= 3; j++)
                    y.m[i][j] = (y.m[i][j] + m[i][k] % mod * x.m[k][j] % mod) % mod;
        return y;
    }
};
Mat qpow(Mat x, ll y)
{
    Mat e;
    e.m[1][1] = e.m[2][2] = e.m[3][3] = 1;
    for(; y; y >>= 1, x = x * x)
        if(y & 1) e = e * x;
    return e;
}
int main()
{
    scanf("%lld", &T);
    Mat a;
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            a.m[i][j] = 0;
    a.m[1][1] = 1; a.m[1][3] = 1; a.m[2][1] = 1; a.m[3][2] = 1;
    for(int i = 1; i <= T; i++)
    {
        scanf("%lld", &n);
        Mat res = qpow(a, n - 1);
        Mat ans;
        ans.m[1][1] = 1; ans.m[2][1] = 1; ans.m[3][1] = 1;
        ans = res * ans;
        printf("%lld\n", ans.m[3][1]);
    }
    return 0;
}