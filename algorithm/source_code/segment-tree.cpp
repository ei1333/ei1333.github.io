
template< typename T >
struct SegmentTree
{
  const function< T(T, T) > merge;
  const T INF;

  vector< T > seg;
  int sz;

  SegmentTree(int n, bool ismax = false)
      : INF(ismax ? numeric_limits< T >::min() : numeric_limits< T >::max()),
        merge(ismax ? [&](T a, T b) { return (max(a, b)); } : [&](T a, T b) { return (min(a, b)); })
  {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz - 1, INF);
  }

  void set(int k, int x)
  {
    seg[k + sz - 1] = x;
  }

  void build()
  {
    for(int k = sz - 2; k >= 0; k--) {
      seg[k] = merge(seg[2 * k + 1], seg[2 * k + 2]);
    }
  }

  T rmq(int a, int b, int k, int l, int r)
  {
    if(a >= r || b <= l) return (INF);
    if(a <= l && r <= b) return (seg[k]);
    return (min(rmq(a, b, 2 * k + 1, l, (l + r) >> 1),
                rmq(a, b, 2 * k + 2, (l + r) >> 1, r)));
  }

  T rmq(int a, int b)
  {
    return (rmq(a, b, 0, 0, sz));
  }

  void update(int k, T x)
  {
    k += sz - 1;
    seg[k] = x;
    while(k > 0) {
      k = (k - 1) >> 1;
      seg[k] = merge(seg[2 * k + 1], seg[2 * k + 2]);
    }
  }
};
