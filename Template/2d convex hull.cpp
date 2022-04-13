#include <iostream>
#include <algorithm>
#include <iomanip>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::sort;

const double eps = 1e-8;
int sgn(double a) { return a < -eps ? -1 : a > eps; }
int cmp(double a, double b) { return sgn(a - b); }

double sqr(double x) { return x * x; }

class V {
    protected:
    	double x, y;
    public:
    	V() { x = y = 0; }
    	V(double _x, double _y) : x(_x), y(_y) {}
    	//...
    	V operator + (const V& o) const { return V(x + o.x, y + o.y); }
		V operator - (const V& o) const { return V(x - o.x, y - o.y); }
		V operator * (double k) const { return V(x * k, y * k); }
		V operator / (double k) const { return V(x / k, y / k); }
		
		double operator [](int i) const { return i == 0 ? x : y; }
		
		double norm2() const { return sqr(x) + sqr(y); }
		double norm() const { return sqrt(norm2()); }
		double arg() const { return atan2(y, x); }
		
		V operator ~() const { return *this / norm(); }
		
		friend double dot(const V& a, const V& b) { return a.x * b.x + a.y * b.y; }
		friend double det(const V& a, const V& b) { return a.x * b.y - b.x * a.y; }
		
		friend double dis(const V& a, const V& b) { return (a - b).norm(); }
		friend double irad(const V& a, const V& b) { return atan2(det(a, b), dot(a, b)); }
		
		V rot(double a) { return V(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }

		V perp() const { return V(-y, x); }
};
class P : public V {
    protected:
    	int i;
    public:
    	P() { x = y = 0; }
    	P(double _x, double _y, int _i = -1): V(_x, _y), i(_i) {}
    	//...
    	V operator - (const P& o) const { return V(x - o.x, y - o.y); }
    	P operator + (const V& o) const { return P(x + o[0], y + o[1]); }
    	
    	bool operator < (const P& p) const {
			if(cmp(this->x, p.x) == 0) return cmp(this->y, p.y) == -1;
			else return cmp(this->x, p.x) == -1;
		}
    	
    	void shake(double e = eps) {
		    srand(time(0));
		    x += (rand() / (double)RAND_MAX - 0.5) * e;
		    y += (rand() / (double)RAND_MAX - 0.5) * e;
		}
};
class S {
    protected:
    	P u, v;
    public:
    	S() {}
    	S(P _u, P _v) : u(_u), v(_v) {}
    	double len() const { return dis(u, v); }
    	V dir() const { return u - v; }
    	//...
    	P operator [](int i) const { return i == 0 ? u : v; }
};
class L : public S {
    protected:
    public:
    	L() {}
    	L(P _u, P _v) : S(_u, _v) {}
    	//...
    	friend double dist(const L& l, const P& p) {
		    return fabs(det(p - l[0], l[1] - l[0]) / l.len());
		}
		
		friend P defpoint(const L& l, double k) {
		    return l[0] + l.dir() * k;
		}
		
		friend P proj(const L& l, const P& p) {
		    return l[0] + ~l.dir() * dot(p - l[0], l[1] - l[0]) / l.len();
		}
};
class C {
    protected:
    	P o;
    	double r;
   	public:
    	C() {}
    	C(P _o, double _r) : o(_o), r(_r) {}
    	//...
};
class CH {
    protected:
    	int n;
    	P* p;
   	public:
    	CH() : n(0), p(NULL) {}
    	CH(int _n) : n(0) { p = (P*)calloc(_n, sizeof(P)); }
    	//...
    	P operator [](int i) const { return p[i]; }
    	
    	void push_back(const P& _p) { p[n++] = _p; }
    	void pop_back() { n--; }
    	int size() { return n; }
    	double sumPointDist() {
    		double sum = dis(p[n-1], p[0]);
    		for(int i = 1; i < n; i++) sum += dis(p[i], p[i-1]);
			return sum;
		}
};

CH graham(int n, P p[]) {
	int b = 0;
	for(int i = 1; i < n; i++) {
		if(p[i] < p[b]) { b = i; }
	}
	swap(p[0], p[b]);
	sort(p + 1, p + n, [&p](const P& u, const P& v) {
		return sgn(det(u - *p, v - *p)) > 0 || (sgn(det(u - *p, v - *p)) == 0 && sgn(dis(u, *p) - dis(v, *p)) < 0); 
	});
	CH ch(n);
	ch.push_back(p[0]), ch.push_back(p[1]);
	for(int i = 2; i < n; i++) {
		int ls = ch.size() - 1;
		while(ls > 0 && sgn(det(p[i] - ch[ls - 1], ch[ls] - ch[ls - 1])) >= 0) {
			ch.pop_back(), --ls;
		}
		ch.push_back(p[i]);
	}
	return ch;
}
int main()
{
	int n;
	cin >> n;
	P* p = new P[n];
	for(int i = 0; i < n; i++)
	{
		double x, y;
		cin >> x >> y;
		p[i] = P(x, y, i);
	}
	CH ch = graham(n, p);
	cout << std::setiosflags(std::ios::fixed);
	cout << std::setprecision(2) << ch.sumPointDist() << endl;
	return 0;
}
