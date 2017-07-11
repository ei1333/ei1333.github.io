const int _base = 1e9 + 7;

struct RollingHash
{
  vector< unsigned > hashed, power;
  RollingHash(const string& s)
  {
    int sz = s.size();
    hashed.assign(sz + 1, 0);
    power.assign(sz + 1, 0);
 
    power[0] = 1;
    for(int i = 0; i < sz; i++) {
      power[i + 1] = power[i] * _base;
    }
    for(int i = 0; i < sz; i++) {
      hashed[i + 1] = (hashed[i] + s[i]) * _base;
    }
  }
  unsigned get(int l, int r) // [l, r)
  {
    return((hashed[r] - hashed[l] * power[r - l]));
  }
  unsigned connect(int h1, int h2, int h2len)
  {
    return(h1 * power[h2len] + h2);
  }
  int LCP(RollingHash& b, int l1, int r1, int l2, int r2)
  {
    int len = min(r1 - l1, r2 - l2);
    int low = -1, high = len + 1;
    while(high - low > 1) {
      int mid = (low + high) >> 1;
      if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
      else high = mid;
    }
    return(low);
  }
};
