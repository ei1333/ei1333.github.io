enum
{
  OUT, ON, IN
};
int Contains(const Polygon &Q, const Point &p)
{
  bool in = false;
  for(int i = 0; i < Q.size(); i++) {
    Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
    if(a.y > b.y) swap(a, b);
    if(a.y <= 0 && 0 < b.y && cross(a, b) < 0) in = !in;
    if(cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}
