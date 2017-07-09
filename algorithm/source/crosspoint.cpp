Point Crosspoint(const Line &l, const Line &m)
{
  double A = cross(l.b - l.a, m.b - m.a);
  double B = cross(l.b - l.a, l.b - m.a);
  if(abs(A) < EPS && abs(B) < EPS) return m.a;
  return m.a + (m.b - m.a) * B / A;
}

Point Crosspoint(const Segment &l, const Segment &m)
{
  double A = cross(l.b - l.a, m.b - m.a);
  double B = cross(l.b - l.a, l.b - m.a);
  if(abs(A) < EPS && abs(B) < EPS) return m.a;
  return m.a + (m.b - m.a) * B / A;
}

PointPoint Crosspoint(const Circle &c, const Line l)
{
  Point hp = Projection(l, c.p), h = hp - c.p;
  const double d2 = h.norm();
  Point v = (l.b - l.a) * sqrt(c.r * c.r - d2) / (l.b - l.a).abs();
  return PointPoint(hp - v, hp + v);
}

PointPoint Crosspoint(const Circle &c, const Segment &l)
{
  Line aa = Line(l.a, l.b);
  if(Intersect(c, l) == 2) return Crosspoint(c, aa);
  PointPoint ret = Crosspoint(c, aa);
  if(dot(l.a - ret.first, l.b - ret.first) < 0) ret.second = ret.first;
  else ret.first = ret.second;
  return ret;
}

PointPoint Crosspoint(const Circle &c1, const Circle &c2)
{
  double d = (c1.p - c2.p).abs();
  double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
  double t = atan2(c2.p.y - c1.p.y, c2.p.x - c1.p.x);
  Point p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);
  Point p2 = c1.p + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);
  return (PointPoint(p1, p2));
}
