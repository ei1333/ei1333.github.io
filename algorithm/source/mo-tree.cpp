struct Mo_Tree_Vertex
{
  vector< vector< int > > g, parent;
  vector< int > vs, in;

  vector< int > left, right, order, lca, dep;
  vector< bool > v;
  int width;
  int nl, nr, ptr;

  Mo_Tree_Vertex(int n) : width((int) sqrt(2 * n - 1)), nl(0), nr(0), ptr(0), g(n), in(n), dep(n), v(n)
  {
    const auto lg = (int) (log2(n) + 1);
    parent.resize(lg, vector< int >(n));
    vs.reserve(2 * n - 1);
  }

  void add_edge(int x, int y)
  {
    g[x].push_back(y);
    g[y].push_back(x);
  }

  void dfs(int idx, int depth, int par)
  {
    in[idx] = (int) vs.size();
    dep[idx] = depth;
    parent[0][idx] = par;
    vs.push_back(idx);
    for(auto &to : g[idx]) {
      if(to == par) continue;
      dfs(to, depth + 1, idx);
      vs.push_back(to); // 本来のEuler-tourはidxだが, 今回は深い方の頂点をとりたいのでto
    }
  }

  int getlca(int u, int v)
  {
    if(dep[u] > dep[v]) swap(u, v);
    for(int k = 0; k < parent.size(); k++) {
      if(((dep[v] - dep[u]) >> k) & 1) {
        v = parent[k][v];
      }
    }
    if(u == v) return (u);
    for(int k = (int) parent.size() - 1; k >= 0; k--) {
      if(parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return (parent[0][u]);
  }

  void insert(int x, int y)
  {
    if(in[x] > in[y]) swap(x, y);
    left.push_back(in[x] + 1);
    right.push_back(in[y] + 1);
    lca.push_back(getlca(x, y));
  }

  void prepare()
  {
    dfs(0, 0, -1);
    for(int k = 0; k + 1 < parent.size(); k++) {
      for(int i = 0; i < parent[k].size(); i++) {
        if(parent[k][i] == -1) parent[k + 1][i] = -1;
        else parent[k + 1][i] = parent[k][parent[k][i]];
      }
    }
  }

  void build()
  {
    order.resize(left.size());
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order), [&](int a, int b)
    {
      if(left[a] / width != left[b] / width) return left[a] < left[b];
      return right[a] < right[b];
    });
  }

  int process()
  {
    if(ptr == order.size()) return (-1);
    if(ptr > 0) distribute(lca[order[ptr - 1]]); // 前のクエリで追加したLCAを削除
    const auto id = order[ptr];
    while(nl > left[id]) distribute(vs[--nl]);
    while(nr < right[id]) distribute(vs[nr++]);
    while(nl < left[id]) distribute(vs[nl++]);
    while(nr > right[id]) distribute(vs[--nr]);
    distribute(lca[id]); // LCA の頂点を例外として追加する
    return (order[ptr++]);
  }

  /* 偶数回目の訪問時は削除, 奇数回目の訪問時は追加を呼び出す */
  inline void distribute(int vertex)
  {
    v[vertex].flip();
    if(v[vertex]) add(vertex);
    else del(vertex);
  }

  void add(int idx);

  void del(int idx);
};
