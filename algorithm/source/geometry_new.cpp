const double EPS = 1e-8, PI = acos(-1);

inline bool eq(double a, double b) { return fabs(b - a) < EPS; }

using Point = complex< double >;

istream &operator>>(istream &is, Point &p) {
  double a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}

ostream &operator<<(ostream &os, Point &p) {
  os << fixed << setprecision(10) << p.real() << " " << p.imag();
}

Point rotate(double theta, const Point &p) {
  return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

double radian_to_degree(double r) {
  return (r * 180.0 / PI);
}

double degree_to_radian(double d) {
  return (d * PI / 180.0);
}

double get_angle(const Point &a, const Point &b, const Point &c) {
  const Point v(b - a), w(c - b);
  double alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
  if(alpha > beta) swap(alpha, beta);
  double theta = (beta - alpha);
  return min(theta, 2 * acos(-1) - theta);
}

namespace std {
  bool operator<(const Point &a, const Point &b) {
    return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
  }
}


struct Line {
  Point a, b;

  Line() {}

  Line(Point a, Point b) : a(a), b(b) {}

  Line(double A, double B, double C) // Ax + By = C
  {
    if(eq(A, 0)) a = Point(0, C / B), b = Point(1, C / B);
    else if(eq(B, 0)) b = Point(C / A, 0), b = Point(C / A, 1);
    else a = Point(0, C / B), b = Point(C / A, 0);
  }

  friend ostream &operator<<(ostream &os, Line &p) {
    return os << p.a << " to " << p.b;
  }

  friend istream &operator>>(istream &is, Line &a) {
    return is >> a.a >> a.b;
  }
};

struct Segment : Line {
  Segment() {}

  Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
  Point p;
  double r;

  Circle() {}

  Circle(Point p, double r) : p(p), r(r) {}
};

using Points = vector< Point >;
using Polygon = vector< Point >;
using Segments = vector< Segment >;
using Lines = vector< Line >;
using Circles = vector< Circle >;

double cross(const Point &a, const Point &b) {
  return real(a) * imag(b) - imag(a) * real(b);
}

double dot(const Point &a, const Point &b) {
  return real(a) * real(b) + imag(a) * imag(b);
}

int ccw(const Point &a, Point b, Point c) {
  b = b - a, c = c - a;
  if(cross(b, c) > EPS) return +1;  // "COUNTER_CLOCKWISE"
  if(cross(b, c) < -EPS) return -1; // "CLOCKWISE"
  if(dot(b, c) < 0) return +2;      // "ONLINE_BACK"
  if(norm(b) < norm(c)) return -2;  // "ONLINE_FRONT"
  return 0;                         // "ON_SEGMENT"
}

bool parallel(const Line &a, const Line &b) {
  return abs(cross(a.b - a.a, b.b - b.a)) < EPS;
}

bool orthogonal(const Line &a, const Line &b) {
  return abs(cross(a.a - a.b, b.a - b.b)) < EPS;
}

Point projection(const Line &l, const Point &p) {
  double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
  double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

Point reflection(const Line &l, const Point &p) {
  return p + (projection(l, p) - p) * 2.0;
}

bool Intersect(const Line &l, const Point &p) {
  return abs(ccw(l.a, l.b, p)) != 1;
}


bool intersect(const Line &l, const Line &m) {
  return abs(cross(l.b - l.a, m.b - m.a)) > EPS || abs(cross(l.b - l.a, m.b - l.a)) < EPS;
}

bool intersect(const Segment &s, const Point &p) {
  return ccw(s.a, s.b, p) == 0;
}

bool intersect(const Line &l, const Segment &s) {
  return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
}

double distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) {
  return distance(l, c.p) <= c.r + EPS;
}

bool intersect(const Circle &c, const Point &p) {
  return abs(abs(p - c.p) - c.r) < EPS;
}

bool intersect(const Segment &s, const Segment &t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

int intersect(const Circle &c, const Segment &l) {
  if(norm(projection(l, c.p) - c.p) - c.r * c.r > EPS) return 0;
  const double d1 = abs(c.p - l.a), d2 = abs(c.p - l.b);
  if(d1 < c.r + EPS && d2 < c.r + EPS) return 0;
  if(d1 < c.r - EPS && d2 > c.r + EPS || d1 > c.r + EPS && d2 < c.r - EPS) return 1;
  const Point h = projection(l, c.p);
  if(dot(l.a - h, l.b - h) < 0) return 2;
  return 0;
}

double distance(const Point &a, const Point &b) {
  return abs(a - b);
}

double distance(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}

double distance(const Line &l, const Line &m) {
  return intersect(l, m) ? 0 : distance(l, m.a);
}

double distance(const Segment &s, const Point &p) {
  Point r = projection(s, p);
  if(intersect(s, r)) return abs(r - p);
  return min(abs(s.a - p), abs(s.b - p));
}

double distance(const Segment &a, const Segment &b) {
  if(intersect(a, b)) return 0;
  return min({distance(a, b.a), distance(a, b.b), distance(b, a.a), distance(b, a.b)});
}

double distance(const Line &l, const Segment &s) {
  if(intersect(l, s)) return 0;
  return min(distance(l, s.a), distance(l, s.b));
}

Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l.b - l.a, m.b - m.a);
  double B = cross(l.b - l.a, l.b - m.a);
  if(abs(A) < EPS && abs(B) < EPS) return m.a;
  return m.a + (m.b - m.a) * B / A;
}

Point crosspoint(const Segment &l, const Segment &m) {
  double A = cross(l.b - l.a, m.b - m.a);
  double B = cross(l.b - l.a, l.b - m.a);
  if(abs(A) < EPS && abs(B) < EPS) return m.a;
  return m.a + (m.b - m.a) * B / A;
}

pair< Point, Point > crosspoint(const Circle &c, const Line l) {
  Point hp = projection(l, c.p), h = hp - c.p;
  const double d2 = norm(h);
  Point v = (l.b - l.a) * sqrt(c.r * c.r - d2) / abs(l.b - l.a);
  return {hp - v, hp + v};
}

pair< Point, Point > crosspoint(const Circle &c, const Segment &l) {
  Line aa = Line(l.a, l.b);
  if(intersect(c, l) == 2) return crosspoint(c, aa);
  auto ret = crosspoint(c, aa);
  if(dot(l.a - ret.first, l.b - ret.first) < 0) ret.second = ret.first;
  else ret.first = ret.second;
  return ret;
}

pair< Point, Point > crosspoint(const Circle &c1, const Circle &c2) {
  double d = abs(c1.p - c2.p);
  double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
  double t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
  Point p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);
  Point p2 = c1.p + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);
  return {p1, p2};
}

bool is_convex(const Polygon &p) {
  int n = (int) p.size();
  for(int i = 0; i < n; i++) {
    if(ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == -1) return false;
  }
  return true;
}

Polygon convex_hull(Polygon &p) {
  int n = (int) p.size(), k = 0;
  if(n <= 2) return p;
  sort(p.begin(), p.end());
  vector< Point > ch(2 * n);
  for(int i = 0; i < n; ch[k++] = p[i++]) {
    while(k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < 0) --k;
  }
  for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
    while(k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < 0) --k;
  }
  ch.resize(k - 1);
  return ch;
}

enum {
  OUT, ON, IN
};

int contains(const Polygon &Q, const Point &p) {
  bool in = false;
  for(int i = 0; i < Q.size(); i++) {
    Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
    if(a.imag() > b.imag()) swap(a, b);
    if(a.imag() <= 0 && 0 < b.imag() && cross(a, b) < 0) in = !in;
    if(cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}


bool merge_if_able(Segment &s1, Segment s2) {
  if(abs(cross(s1.b - s1.a, s2.b - s2.a)) > EPS) return false;
  if(ccw(s1.a, s2.a, s1.b) == 1 || ccw(s1.a, s2.a, s1.b) == -1) return false;
  if(ccw(s1.a, s1.b, s2.a) == -2 || ccw(s2.a, s2.b, s1.a) == -2) return false;
  s1 = Segment(min(s1.a, s2.a), max(s1.b, s2.b));
  return true;
}

void merge_segments(vector< Segment > &segs) {
  for(int i = 0; i < segs.size(); i++) {
    if(segs[i].b < segs[i].a) swap(segs[i].a, segs[i].b);
  }
  for(int i = 0; i < segs.size(); i++) {
    for(int j = i + 1; j < segs.size(); j++) {
      if(merge_if_able(segs[i], segs[j])) {
        segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}

vector< vector< int > > segment_arrangement(vector< Segment > &segs, vector< Point > &ps) {
  vector< vector< int > > g;
  int N = (int) segs.size();
  for(int i = 0; i < N; i++) {
    ps.emplace_back(segs[i].a);
    ps.emplace_back(segs[i].b);
    for(int j = i + 1; j < N; j++) {
      const Point p1 = segs[i].b - segs[i].a;
      const Point p2 = segs[j].b - segs[j].a;
      if(cross(p1, p2) == 0) continue;
      if(intersect(segs[i], segs[j])) {
        ps.emplace_back(crosspoint(segs[i], segs[j]));
      }
    }
  }
  sort(begin(ps), end(ps));
  ps.erase(unique(begin(ps), end(ps)), end(ps));

  int M = (int) ps.size();
  g.resize(M);
  for(int i = 0; i < N; i++) {
    vector< int > vec;
    for(int j = 0; j < M; j++) {
      if(intersect(segs[i], ps[j])) {
        vec.emplace_back(j);
      }
    }
    for(int j = 1; j < vec.size(); j++) {
      g[vec[j - 1]].push_back(vec[j]);
      g[vec[j]].push_back(vec[j - 1]);
    }
  }
  return (g);
}

Polygon convex_cut(Polygon &U, Line l) {
  Polygon ret;
  for(int i = 0; i < U.size(); i++) {
    Point now = U[i], nxt = U[(i + 1) % U.size()];
    if(ccw(l.a, l.b, now) != -1) ret.push_back(now);
    if(ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
      ret.push_back(crosspoint(Line(now, nxt), l));
    }
  }
  return (ret);
}

double area2(const Polygon &p) {
  double A = 0;
  for(int i = 0; i < p.size(); ++i) {
    A += cross(p[i], p[(i + 1) % p.size()]);
  }
  return A;
}

double convex_diameter(Polygon &p) {
  int N = (int) p.size();
  int is = 0, js = 0;
  for(int i = 1; i < N; i++) {
    if(p[i].imag() > p[is].imag()) is = i;
    if(p[i].imag() < p[js].imag()) js = i;
  }
  double maxdis = norm(p[is] - p[js]);

  int maxi, maxj, i, j;
  i = maxi = is;
  j = maxj = js;
  do {
    if(cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
      j = (j + 1) % N;
    } else {
      i = (i + 1) % N;
    }
    if(norm(p[i] - p[j]) > maxdis) {
      maxdis = norm(p[i] - p[j]);
      maxi = i;
      maxj = j;
    }
  } while(i != is || j != js);
  return sqrt(maxdis);
}

pair< Point, Point > closer(const pair< Point, Point > &a, const pair< Point, Point > &b) {
  return distance(a.first, a.second) < distance(b.first, b.second) ? a : b;
}

pair< Point, Point > closest_pair_util(Points &ps, int l, int r) {
  if(r - l == 2) {
    return {ps[l], ps[l + 1]};
  }
  if(r - l == 3) {
    pair< Point, Point > a(ps[l], ps[l + 1]), b(ps[l + 1], ps[l + 2]), c(ps[l], ps[l + 2]);
    return closer(a, closer(b, c));
  }

  int mid = (l + r) / 2;
  Point midPoint = ps[mid];
  auto res = closer(closest_pair_util(ps, l, mid), closest_pair_util(ps, mid, r));
  double d = distance(res.first, res.second);

  Points pos[2];
  for(int i = l; i < r; ++i) {
    if(abs(ps[i].real() - midPoint.real()) < d) pos[i < mid].push_back(ps[i]);
  }
  for(const auto &i : pos[0]) {
    for(const auto &j : pos[1]) {
      if(distance(i, j) < d) {
        d = distance(i, j);
        res = {i, j};
      }
    }
  }
  return res;
}

pair< Point, Point > closest_pair(Points ps) {
  if(ps.size() <= 1) exit(-1);
  for(int i = 0; i < ps.size(); ++i) {
    ps[i] = rotate(0.1, ps[i]);
  }
  sort(ps.begin(), ps.end());
  if(ps.size() == 2) return {ps[0], ps[1]};
  auto res = closest_pair_util(ps, 0, ps.size());
  res.first = rotate(-0.1, res.first);
  res.second = rotate(-0.1, res.second);
  return res;
}
