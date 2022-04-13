#include <iostream>
#include <iomanip>
#include <unordered_map>

#include <cmath>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

const double eps = 1e-5, _eps = 1e-8;
int sgn(double a) { return a < -eps ? -1 : a > eps; }
int cmp(double a, double b) { return sgn(a - b); }
double sqr(double x) { return x * x; }

namespace ComputationalGeometry_3D {
	class V {
		protected:
			double x, y, z;
		public:
			V() : x(0), y(0), z(0) {}
			V(double x, double y, double z) : x(x), y(y), z(z) {}
			V operator + (const V& o) const { return V(x + o.x, y + o.y, z + o.z); }
			V operator - (const V& o) const { return V(x - o.x, y - o.y, z - o.z); }
			V operator * (double k) const { return V(x * k, y * k, z * k); }
			V operator / (double k) const { return V(x / k, y / k, z / k); }
			double operator [](int i) const { return i == 0 ? x : (i == 1 ? y : z); }
			double norm2() const { return sqr(x) + sqr(y) + sqr(z); }
			double norm() const { return sqrt(norm2()); }
			V operator ~() const { return *this / norm(); }
			friend double dot(const V& a, const V& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
			friend V det(const V& a, const V& b) { return V(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - b.x * a.y); }
	};
	class P : public V {
		protected:
			int id;
		public:
			P() : V(0, 0, 0) {}
			P(double x, double y, double z) : V(x, y, z) {}
			P(double x, double y, double z, int id) : V(x, y, z), id(id) {}
			V operator - (const P& o) const {return V(x - o.x, y - o.y, z - o.z);}
			friend std::istream& operator >> (std::istream& input, P& p) {
				input >> p.x >> p.y >> p.z;
				return input;
			}
			friend std::ostream& operator << (std::ostream& output, const P& p) {
				output << '(' << p.x << ',' << p.y << ',' << p.z << ')';
				return output;
			}
			int getId() { return id; }
			void setId(int id) { this->id = id; }
			void shake(double e = eps) {
				srand(time(0));
				x += (rand() / (double)RAND_MAX - 0.5) * e;
				y += (rand() / (double)RAND_MAX - 0.5) * e;
				z += (rand() / (double)RAND_MAX - 0.5) * e;
			}
	};
	class F {
		protected:
			P p[3];
		public:
			F() {}
			F(P u, P v, P w) : p{u, v, w} {}
			P operator [](int i) const { return p[i]; }
			V operator ~() const { return det(p[1] - p[0], p[2] - p[0]); }
			double area() const { return (~*this).norm() / 2; }
	};
	bool atouterside(const P& p, const F& f) { return sgn(dot(p - f[0], ~f)) >= 0; }
	double projon(const V& u, const V& v) { return dot(u, v) / v.norm(); }
	double PdistoF(const P& p, const F& f) { return projon(p - f[0], ~f); }
	class CH {
		protected:
			int n;
			F* f;
		public:
			CH() : n(0), f(nullptr) {}
			CH(int _n) : n(0) { f = (F*)calloc(_n, sizeof(F)); }
			int getSize() const { return n; }
			F operator [](int i) const { return f[i]; }
			void clear() { delete[] f; }
			void push_back(F _f) { f[n++] = _f; }
			void resetSize(int _n) { n = 0, f = (F*)calloc(_n, sizeof(F)); }
			double area() const {
				double ret = 0;
				for(int i = 0; i < n; i++) ret += f[i].area();
				return ret;
			}
	};
	CH incremental(int n, P p[]) {
		CH ch(n), tp(n);
		ch.push_back(F(p[0], p[1], p[2]));
		ch.push_back(F(p[2], p[1], p[0]));
		std::unordered_map <int, bool> illuminatedDirectedEdge;
		for(int i = 3; i < n; i++) {
			P a = p[i];
			for(int j = 0; j < ch.getSize(); j++) {
				bool outside = atouterside(a, ch[j]);
				if (!outside) tp.push_back(ch[j]);
				for (int k = 0; k < 3; k++) {
					illuminatedDirectedEdge[ch[j][k].getId() * n + ch[j][(k + 1) % 3].getId()] = outside;
				}
			}
			for (int j = 0; j < ch.getSize(); j++) {
				for (int k = 0; k < 3; k++) {
					int x = ch[j][k].getId(), y = ch[j][(k + 1) % 3].getId();
					if (illuminatedDirectedEdge[x * n + y] && !illuminatedDirectedEdge[y * n + x]) {
						tp.push_back(F(p[x], p[y], a));
					}
				}
			}
			std::swap(ch, tp);
			tp.clear(), tp.resetSize(n);
		}
		return ch;
	}
} using namespace ComputationalGeometry_3D;
const int N = 2005;
int n; P p[N];
int main() {
	cin.sync_with_stdio(false);
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> p[i], p[i].setId(i), p[i].shake(_eps);
	}
	CH ch = incremental(n, p);
	cout << std::fixed << std::setprecision(3) << ch.area() << endl;
	return 0;
}
