double Area2(const Polygon &p)
{
  double A = 0;
  for(int i = 0; i < p.size(); ++i) {
    A += cross(p[i], p[(i + 1) % p.size()]);
  }
  return A;
}
