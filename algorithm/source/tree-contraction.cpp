struct edge
{
  int to;
  int cost;
};

struct TreeContraction
{
  vector< vector< edge > > g;
  vector< int > marker, order, parent;

  TreeContraction(int n)
  {
    g.resize(n);
    destroy();
  }

  void destroy()
  {
    marker.assign(g.size(), 0);
  }

  void add_edge(int idx, const edge &e)
  {
    g[idx].emplace_back(e);
  }

  void build()
  {
    function< void(int, int) > dfs = [&](int idx, int par)
    {
      for(auto &e : g[idx]) {
        if(e.to == par) continue;
        dfs(e.to, idx);
      }
      parent[idx] = par;
      order.emplace_back(idx);
    };
    parent.resize(g.size());
    dfs(0, -1);
    order.pop_back();
  }

  inline void mark(int x)
  {
    marker[x] = 2;
  }

  inline
  inline void contract(vector< vector< edge > > &gg)
  {
    for(int i : order) if(marker[i] >= 1) ++marker[parent[i]];
    gg.clear();
    gg.resize(N);

    function< edge(int, int) > contraction = [&](int idx, int par)
    {
      if(marker[idx] == 0) return (edge) {-1};
      for(auto &e : g[idx]) {
        if(e.to == par) continue;
        auto ret = contraction(e.to, idx);
        if(ret.to == -1) continue;

        // この下を変更する
        ret.cost += e.cost;
        if(marker[idx] == 1) {
          return (ret);
        } else {
          gg[idx].emplace_back(ret);
          gg[ret.to].emplace_back((edge) {idx, ret.cost});
        }
      }
      return ((edge) {idx, 0});
    };
    contraction(0, -1);
  }
};

