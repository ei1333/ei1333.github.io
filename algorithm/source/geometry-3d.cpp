
const double EPS = 1e-8, PI = acos(-1);

inline bool eq(double a, double b) { return fabs(b - a) < EPS; }

struct Point3D
{
  double x, y, z;

  Point3D() {}

  Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

  Point3D operator+(const Point3D &b) const { return Point3D(x + b.x, y + b.y, z + b.z); }

  Point3D operator-(const Point3D &b) const { return Point3D(x - b.x, y - b.y, z - b.z); }

  Point3D operator*(const double b) const { return Point3D(x * b, y * b, z * b); }

  Point3D operator/(const double b) const { return Point3D(x / b, y / b, z / b); }

  double norm() { return x * x + y * y + z * z; }

  double abs() { return sqrt(norm()); }

  friend ostream &operator<<(ostream &os, Point3D &p) { return os << "(" << p.x << "," << p.y << "," << p.z << ")"; }

  friend istream &operator>>(istream &is, Point3D &a) { return is >> a.x >> a.y >> a.z; }
};


double dot(const Point3D &a, const Point3D &b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3D cross(const Point3D &a, const Point3D &b)
{
  return (Point3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

struct Line3D
{
  Point3D a, b;

  Line3D() {}

  Line3D(Point3D a, Point3D b) : a(a), b(b) {}
};

struct Segment3D
{
  Point3D a, b;

  Segment3D() {}

  Segment3D(Point3D a, Point3D b) : a(a), b(b) {}
};

struct Sphere
{
  Point3D p;
  double r;

  Sphere() {}

  Sphere(Point3D p, double r) : p(p), r(r) {}
};

Point3D Projection(const Line3D &l, const Point3D &p)
{
  double t = dot(p - l.a, l.a - l.b) / (l.a - l.b).norm();
  return l.a + (l.a - l.b) * t;
}

Point3D Projection(const Segment3D &l, const Point3D &p)
{
  double t = dot(p - l.a, l.a - l.b) / (l.a - l.b).norm();
  return l.a + (l.a - l.b) * t;
}

Point3D Reflection(const Line3D &l, const Point3D &p)
{
  return p + (Projection(l, p) - p) * 2.0;
}


double Distance(const Line3D &l, const Point3D &p)
{
  return ((cross(l.b - l.a, p - l.a) / (l.b - l.a).abs()).abs());
}

double Distance(const Segment3D &s, const Point3D &p)
{
  if(dot(s.b - s.a, p - s.a) < 0) return ((p - s.a).abs());
  if(dot(s.a - s.b, p - s.b) < 0) return ((p - s.b).abs());
  return (Distance(Line3D(s.a, s.b), p));
}

bool Intersect(const Sphere &c, const Segment3D &s)
{
  double d = Distance(s, c.p);
  if(d > c.r) return (false);
  return ((s.a - c.p).abs() > c.r || (s.b - c.p).abs() > c.r);
}

pair< Point3D, Point3D > Crosspoint(const Sphere &c, const Line3D &l)
{
  Point3D hp = Projection(l, c.p), h = hp - c.p;
  const double d2 = h.norm();
  Point3D v = (l.b - l.a) * sqrt(c.r * c.r - d2) / (l.b - l.a).abs();
  return {hp - v, hp + v};
}

pair< Point3D, Point3D > Crosspoint(const Sphere &c, const Segment3D &l)
{
  Segment3D aa(l.a, l.b);
  if(Intersect(c, l) == 2) return Crosspoint(c, Line3D(aa.a, aa.b));
  auto ret = Crosspoint(c, Line3D(aa.a, aa.b));
  if(dot(l.a - ret.first, l.b - ret.first) < 0) ret.second = ret.first;
  else ret.first = ret.second;
  return (ret);
}

