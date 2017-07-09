bool Intersect(const Line &l, const Point &p)
{
  return abs(ccw(l.a, l.b, p)) != 1;
}

bool Intersect(const Line &l, const Line &m)
{
  return abs(cross(l.b - l.a, m.b - m.a)) > EPS || abs(cross(l.b - l.a, m.b - l.a)) < EPS;
}

bool Intersect(const Segment &s, const Point &p)
{
  return ccw(s.a, s.b, p) == 0;
}

bool Intersect(const Line &l, const Segment &s)
{
  return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
}

bool Intersect(const Segment &s, const Segment &t)
{
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

bool Intersect(const Circle &c, const Line &l)
{
  return Distance(l, c.p) <= c.r + EPS;
}

bool Intersect(const Circle &c, const Point &p)
{
  return abs((p - c.p).abs() - c.r) < EPS;
}

int Intersect(const Circle &c, const Segment &l)
{
  if((Projection(l, c.p) - c.p).norm() - c.r * c.r > EPS) return 0;
  const double d1 = (c.p - l.a).abs(), d2 = (c.p - l.b).abs();
  if(d1 < c.r + EPS && d2 < c.r + EPS) return 0;
  if(d1 < c.r - EPS && d2 > c.r + EPS || d1 > c.r + EPS && d2 < c.r - EPS) return 1;
  const Point h = Projection(l, c.p);
  if(dot(l.a - h, l.b - h) < 0) return 2;
  return 0;
}
