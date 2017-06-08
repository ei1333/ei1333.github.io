
template< typename T >
struct SegmentTree
{
  const function< T(T, T) > merge;
  const T INF;

  vector< T > seg, add;
  int sz;


  SegmentTree(int n, bool ismax = false)
      : INF(ismax ? numeric_limits< T >::min() / 5 : numeric_limits< T >::max() / 5),
        merge(ismax ? [&](T a, T b) { return (max(a, b)); } : [&](T a, T b) { return (min(a, b)); })
  {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz - 1, 0);
    add.assign(2 * sz - 1, 0);
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
    if(a <= l && r <= b) return (seg[k] + add[k]);
    return (merge(rmq(a, b, 2 * k + 1, l, (l + r) >> 1),
                  rmq(a, b, 2 * k + 2, (l + r) >> 1, r)) + add[k]);
  }

  T rmq(int a, int b)
  {
    return (rmq(a, b, 0, 0, sz));
  }

  void rangeadd(int a, int b, int x, int k, int l, int r)
  {
    if(a >= r || b <= l) return;
    if(a <= l && r <= b) {
      add[k] += x;
      return;
    }
    rangeadd(a, b, x, 2 * k + 1, l, (l + r) >> 1);
    rangeadd(a, b, x, 2 * k + 2, (l + r) >> 1, r);
    seg[k] = merge(seg[2 * k + 1] + add[2 * k + 1], seg[2 * k + 2] + add[2 * k + 2]);
  }
};
