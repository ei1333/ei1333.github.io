const double EPS = 1e-8, PI = acos(-1);

inline bool eq(double a, double b) { return fabs(b - a) < EPS; }

struct Point
{
  double x, y;

  Point() {}

  Point(double x, double y) : x(x), y(y) {}

  Point operator+(const Point &b) const { return Point(x + b.x, y + b.y); }

  Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }

  Point operator*(const double b) const { return Point(x * b, y * b); }

  Point operator*(const Point &b) const { return Point(x * b.x - y * b.y, x * b.y + y * b.x); }

  Point operator/(const double b) const { return Point(x / b, y / b); }

  bool operator<(const Point &b) const { return x != b.x ? x < b.x : y < b.y; }

  bool operator==(const Point &b) const { return eq(x, b.x) && eq(y, b.y); }

  double norm() { return x * x + y * y; }

  double arg() { return atan2(x, y); }

  double abs() { return sqrt(norm()); }

  Point rotate(double theta) { return Point(cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y); }

  Point rotate90() { return Point(-y, x); }

  friend ostream &operator<<(ostream &os, Point &p) { return os << "(" << p.x << "," << p.y << ")"; }

  friend istream &operator>>(istream &is, Point &a) { return is >> a.x >> a.y; }
};

double cross(const Point &a, const Point &b)
{
  return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b)
{
  return a.x * b.x + a.y * b.y;
}

double RadianToDegree(double r)
{
  return (r * 180.0 / acos(-1));
}

double DegreeToRadian(double d)
{
  return (d * acos(-1) / 180.0);
}

double GetAngle(const Point &a, const Point &b, const Point &c)
{
  const Point v = b - a, w = c - b;
  double alpha = atan2(v.y, v.x), beta = atan2(w.y, w.x);
  if(alpha > beta) swap(alpha, beta);
  double theta = (beta - alpha);
  return min(theta, 2 * acos(-1) - theta);
}

struct Line
{
  Point a, b;

  Line() {};

  Line(Point a, Point b) : a(a), b(b) {};

  // Ax + By = C
  Line(double A, double B, double C)
  {
    if(eq(A, 0)) {
      a = Point(0, C / B);
      b = Point(1, C / B);
    } else if(eq(B, 0)) {
      a = Point(C / A, 0);
      b = Point(C / A, 1);
    } else {
      a = Point(0, C / B);
      b = Point(C / A, 0);
    }
  }

  friend ostream &operator<<(ostream &os, Line &p) { return os << "(" << p.a.x << "," << p.a.y << ") to (" << p.b.x << "," << p.b.y << ")"; }

  friend istream &operator>>(istream &is, Line &a) { return is >> a.a.x >> a.a.y >> a.b.x >> a.b.y; }
};

struct Segment
{
  Point a, b;

  Segment() {};

  Segment(Point a, Point b) : a(a), b(b) {};

  friend ostream &operator<<(ostream &os, Segment &p) { return os << "(" << p.a.x << "," << p.a.y << ") to (" << p.b.x << "," << p.b.y << ")"; }

  friend istream &operator>>(istream &is, Segment &a) { return is >> a.a.x >> a.a.y >> a.b.x >> a.b.y; }
};

struct Circle
{
  Point p;
  double r;

  Circle() {};

  Circle(Point p, double r) : p(p), r(r) {};
};

typedef vector< Point > Polygon;
typedef vector< Segment > Segments;
typedef vector< Line > Lines;
typedef vector< Circle > Circles;
typedef pair< Point, Point > PointPoint;
