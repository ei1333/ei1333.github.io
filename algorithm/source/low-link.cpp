struct LowLink
{
  UnionFind uf;
  vector< vector< int > > g;
  vector< int > used, ord, low, parent;

  LowLink(size_t v) : g(v), used(v, 0), ord(v), low(v), uf(v), parent(v, -1) {}

  virtual void add_edge(int x, int y)
  {
    g[x].push_back(y);
    g[y].push_back(x);
  }

  void dfs(int idx, int &k, int par = -1)
  {
    used[idx] = true;
    ord[idx] = k++;
    low[idx] = ord[idx];

    for(auto &to : g[idx]) {
      if(!used[to]) {
        dfs(to, k, idx);
        low[idx] = min(low[idx], low[to]);
        parent[to] = idx;
        if(ord[idx] >= low[to]) uf.unite(idx, to);
      } else if(to != par) {
        low[idx] = min(low[idx], ord[to]);
      }
    }
  }

  void dfs()
  {
    int k = 0;
    dfs(0, k);
  }
};
