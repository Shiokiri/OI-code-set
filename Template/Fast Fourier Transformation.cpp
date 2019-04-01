#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;
const int N = 4.2e6;
const double PI = acos(-1);
int n, r[N];
struct Complex {
    double r, i;
    inline Complex() { r = i = 0; }
    inline Complex(register double x, register double y) { r = x; i = y; }
    inline Complex operator + (register Complex &x) { return Complex(r + x.r, i + x.i); }
    inline Complex operator - (register Complex &x) { return Complex(r - x.r, i - x.i); }
    inline Complex operator * (register Complex &x) { return Complex(r * x.r - i * x.i, r * x.i + i * x.r); }
    inline void operator += (register Complex &x) { r += x.r; i += x.i; }
    inline void operator *= (register Complex &x) { register double t = r; r =  r * x.r - i * x.i; i = t * x.i + i * x.r; }
}f[N], g[N];
inline void FFT(register Complex *a, register int op)
{
    register Complex W, w, t, *a0, *a1;
    register int i, j, k;
    for(i = 0; i < n; ++i)
        if(i < r[i]) t = a[i], a[i] = a[r[i]], a[r[i]] = t;
    for(i = 1; i < n; i <<= 1)
        for(W = Complex(cos(PI/i), sin(PI/i) * op), j = 0; j < n; j += i << 1)
            for(w = Complex(1, 0), a1 = i + (a0 = a + j), k = 0; k < i; ++k, ++a0, ++a1, w *= W)
                t = *a1 * w, *a1 = *a0 - t, *a0 += t;
}
int main()
{
    register int m, i, l = 0;
    scanf("%d%d", &n, &m);
    for(i = 0; i <= n; ++i) scanf("%lf", &f[i].r);
    for(i = 0; i <= m; ++i) scanf("%lf", &g[i].r);
    for(m += n, n = 1; n <= m; n <<= 1, ++l);
    for(i = 0; i < n; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(f, 1); FFT(g, 1);
    for(i = 0; i < n; ++i) f[i] *= g[i];
    FFT(f, -1);
    for(i = 0; i <= m; ++i) printf("%.0lf ", fabs(f[i].r) / n);
    return 0;
}