struct SegmentTreeBIT
{
  int sz;
  vector< BinaryIndexedTree > seg;
  vector< vector< int > > beet;

  SegmentTreeBIT(int n)
  {
    sz = 1;
    while(sz < n) sz <<= 1;
    beet.resize(2 * sz - 1);
  }

  void update(int x, int y, int64 z)
  {
    x += sz - 1;
    seg[x].add(lower_bound(begin(beet[x]), end(beet[x]), y) - begin(beet[x]), z);
    while(x > 0) {
      x = (x - 1) >> 1;
      seg[x].add(lower_bound(begin(beet[x]), end(beet[x]), y) - begin(beet[x]), z);
    }
  }

  void build()
  {
    for(int k = beet.size() - 1; k >= 0; k--) {
      sort(begin(beet[k]), end(beet[k]));
      beet[k].erase(unique(begin(beet[k]), end(beet[k])), end(beet[k]));
    }
    for(int k = 0; k < beet.size(); k++) {
      seg.emplace_back(BinaryIndexedTree(beet[k].size()));
    }
  }


  int64 query(int a, int b, int x, int y, int k, int l, int r)
  {
    if(a >= r || b <= l) return (0);
    if(a <= l && r <= b) {
      int p = y, q = x;
      y = lower_bound(begin(beet[k]), end(beet[k]), y) - begin(beet[k]);
      x = lower_bound(begin(beet[k]), end(beet[k]), x) - begin(beet[k]);
      return (seg[k].sum(y) - seg[k].sum(x));
    }
    return (query(a, b, x, y, 2 * k + 1, l, (l + r) >> 1) + query(a, b, x, y, 2 * k + 2, (l + r) >> 1, r));
  }

  int64 query(int a, int b, int x, int y)
  {
    return (query(a, b, x, y, 0, 0, sz));
  }


  void preupdate(int x, int y)
  {
    x += sz - 1;
    beet[x].push_back(y);
    while(x > 0) {
      x = (x - 1) >> 1;
      beet[x].push_back(y);
    }
  }

  void prequery(int a, int b, int x, int y, int k, int l, int r)
  {
    if(a >= r || b <= l) return;
    if(a <= l && r <= b) {
      beet[k].push_back(y);
      beet[k].push_back(x);
      return;
    }
    prequery(a, b, x, y, 2 * k + 1, l, (l + r) >> 1);
    prequery(a, b, x, y, 2 * k + 2, (l + r) >> 1, r);
  }

  void prequery(int a, int b, int x, int y)
  {
    prequery(a, b, x, y, 0, 0, sz);
  }
};
