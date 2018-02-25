struct CentroidDecomposition
{
  vector< list< int > > g;
  vector< int > sub;
  vector< bool > v;

  CentroidDecomposition() {}

  CentroidDecomposition(int sz) { init(sz); }

  void init(int sz)
  {
    g.resize(sz);
    sub.resize(sz);
    v.assign(sz, false);
  }

  inline int build_dfs(int idx, int par)
  {
    sub[idx] = 1;
    auto it = begin(g[idx]);
    while(it != end(g[idx])) {
      if(*it == par) ++it;
      else if(v[*it]) it = g[idx].erase(it);
      else sub[idx] += build_dfs(*it++, idx);
    }
    return (sub[idx]);
  }

  inline int search_centroid(int idx, int par, const int mid)
  {
    for(auto &to : g[idx]) {
      if(to == par) continue;
      if(sub[to] > mid) return search_centroid(to, idx, mid);
    }
    return (idx);
  }

  void centroid_decomp(int idx = 0)
  {
    int centroid = search_centroid(idx, -1, build_dfs(idx, -1) / 2);
    beet(centroid);
    v[centroid] = true;
    for(auto &to : g[centroid]) centroid_decomp(to);
  }

  void beet(int idx);

  void add_edge(int x, int y)
  {
    g[x].emplace_back(y);
    g[y].emplace_back(x);
  }

  list< int > &operator[](int k)
  {
    return g[k];
  }
};

void CentroidDecomposition::beet(int idx)
{
  
}

