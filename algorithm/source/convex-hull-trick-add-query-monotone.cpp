template< class T >
struct ConvexHullTrickAddQueryMonotone
{
  deque< pair< T, T > > L;
  int isdec;

  ConvexHullTrickAddQueryMonotone() : isdec(-1) {}

  inline T getX(const pair< T, T > &a, const T &x)
  {
    return (a.first * x + a.second);
  }

  inline bool check(const pair< T, T > &a, const pair< T, T > &b, const pair< T, T > &c)
  {
    return ((b.first - a.first) * (c.second - b.second) >= (b.second - a.second) * (c.first - b.first));
  }

  inline bool empty() { return (L.empty()); }

  void add(T a, T b)
  {
    pair< T, T > line(a, b);

    if(isdec == -1 && !L.empty()) {
      if(a < L[0].first) isdec = 1;
      else if(a > L[0].first) isdec = 0;
    }

    if(isdec == 1) {
      if(!L.empty() && L.back().first == a) {
        line.second = min(line.second, L.back().second);
        L.pop_back();
      }
      while(L.size() >= 2 && check(L[L.size() - 2], L.back(), line)) L.pop_back();
      L.emplace_back(line);
    } else {
      if(!L.empty() && L.front().first == a) {
        line.second = min(line.second, L.front().second);
        L.pop_front();
      }
      while(L.size() >= 2 && check(line, L[0], L[1])) L.pop_front();
      L.emplace_front(line);
    }
  }

  T getMinimumQuery(T x)
  {
    int low = -1, high = (int) L.size() - 1;
    while(high - low > 1) {
      int mid = (low + high) >> 1;
      if((getX(L[mid], x) >= getX(L[mid + 1], x))) low = mid;
      else high = mid;
    }
    return (getX(L[high], x));
  }

  T getMinimumQueryMonotone(T x)
  {
    while(L.size() >= 2 && getX(L[0], x) >= getX(L[1], x)) {
      L.pop_front();
    }
    return (getX(L[0], x));
  }
};
