Polygon ConvexCut(Polygon &U, Line l)
{
  Polygon ret;
  for(int i = 0; i < U.size(); i++) {
    Point now = curr(U, i), nxt = next(U, i);
    if(ccw(l.a, l.b, now) != -1) ret.push_back(now);
    if(ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
      ret.push_back(Crosspoint(Line(now, nxt), l));
    }
  }
  return (ret);
}
