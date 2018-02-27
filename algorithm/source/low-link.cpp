template< typename G >
struct LowLink
{
  const G &g;
  UnionFind uf;
  vector< int > used, ord, low, parent;

  LowLink(const G &g) : g(g), uf(g.size()), used(g.size()), ord(g.size()), low(g.size()), parent(g.size(), -1) {}

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
