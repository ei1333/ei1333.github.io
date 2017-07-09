bool MergeIfAble(Segment &s1, Segment s2)
{
  if(abs(cross(s1.b - s1.a, s2.b - s2.a)) > EPS) return false;
  if(ccw(s1.a, s2.a, s1.b) == 1 || ccw(s1.a, s2.a, s1.b) == -1) return false;
  if(ccw(s1.a, s1.b, s2.a) == -2 || ccw(s2.a, s2.b, s1.a) == -2) return false;
  s1 = Segment(min(s1.a, s2.a), max(s1.b, s2.b));
  return true;
}

void MergeSegments(vector< Segment > &segs)
{
  for(int i = 0; i < segs.size(); i++) {
    if(segs[i].b < segs[i].a) swap(segs[i].a, segs[i].b);
  }
  for(int i = 0; i < segs.size(); i++) {
    for(int j = i + 1; j < segs.size(); j++) {
      if(MergeIfAble(segs[i], segs[j])) {
        segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}
