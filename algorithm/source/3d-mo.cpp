struct Mo_3D
{
  vector< int > left, right, index, order;
  vector< bool > v;
  int width;
  int nl, nr, time, ptr;

  Mo_3D(int n) : width((int) pow(n, 2.0 / 3.0)), nl(0), nr(0), ptr(0), time(0), v(n) {}

  void insert(int idx, int l, int r) /* [l, r) */
  {
    left.push_back(l);
    right.push_back(r);
    index.push_back(idx);
  }

  void build()
  {
    order.resize(left.size());
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order), [&](int a, int b)
    {
      if(left[a] / width != left[b] / width) return left[a] < left[b];
      if(right[a] / width != right[b] / width) return bool((right[a] < right[b]) ^ (left[a] / width % 2));
      return bool((index[a] < index[b]) ^ (right[a] / width % 2));
    });
  }

  int process()
  {
    if(ptr == order.size()) return (-1);
    const auto id = order[ptr];
    while(time < index[id]) addquery(time++);
    while(time > index[id]) delquery(--time);
    while(nl > left[id]) distribute(--nl);
    while(nr < right[id]) distribute(nr++);
    while(nl < left[id]) distribute(nl++);
    while(nr > right[id]) distribute(--nr);
    return (index[order[ptr++]]);
  }

  inline void distribute(int idx)
  {
    v[idx].flip();
    if(v[idx]) add(idx);
    else del(idx);
  }

  void add(int idx);

  void del(int idx);

  void addquery(int idx);

  void delquery(int idx);
};
