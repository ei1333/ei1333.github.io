struct UnionFindRange
{
  vector< int > data;
  vector< int > left, right;

  UnionFindRange(int sz)
  {
    data.assign(sz, -1);
    left.resize(sz);
    right.resize(sz);
    for(int i = 0; i < sz; i++) left[i] = i;
    for(int i = 0; i < sz; i++) right[i] = i;
  }

  bool unite(int x, int y)
  {
    x = find(x), y = find(y);
    if(x == y) return (false);
    if(data[x] > data[y]) swap(x, y);
    left[x] = min(left[x], left[y]);
    right[x] = max(right[x], right[y]);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }

  pair< int, int > range(int k)
  {
    k = find(k);
    return {left[k], right[k]};
  };

  int find(int k)
  {
    if(data[k] < 0) return (k);
    return (data[k] = find(data[k]));
  }

  int size(int k)
  {
    return (-data[find(k)]);
  }
};
