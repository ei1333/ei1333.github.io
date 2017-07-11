template< typename T >
struct SegmentTree
{
  const T INF;

  vector< T > seg;
  int sz;

  SegmentTree(int n) : INF(numeric_limits< T >::max())
  {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz - 1, INF);
  }

  T merge(T a, T b)
  {
    return(max(a, b));
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
    return (merge(rmq(a, b, 2 * k + 1, l, (l + r) >> 1),
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
