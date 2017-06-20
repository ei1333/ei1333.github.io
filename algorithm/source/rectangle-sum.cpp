struct RectangleUnion
{
  map< int64, int64 > data;
  int64 sum;

  RectangleUnion() : sum(0)
  {
    data[0] = 1LL << 60;
    data[1LL << 60] = 0;
  }

  void addPoint(int64 x, int64 y)
  {
    auto p = data.lower_bound(x);
    if(p->second >= y) return;
    const int64 nxtY = p->second;
    --p;
    while(p->second <= y) {
      auto it = *p;
      p = --data.erase(p);
      sum -= (it.first - p->first) * (it.second - nxtY);
    }
    sum += (x - p->first) * (y - nxtY);
    data[x] = y;
  }

  int64 getSum()
  {
    return (sum);
  }
};
