template< typename G >
struct BiConnectedComponents : LowLink< G >
{
  using LL = LowLink< G >;

  vector< int > comp;

  BiConnectedComponents(const G &g) : LL(g), comp(g.size()) {}

  int operator[](int k)
  {
    return (comp[k]);
  }

  vector< pair< int, int > > build(UnWeightedGraph &t)
  {
    LL::dfs();
    int ptr = 0;
    vector< int > cc(LL::g.size());
    for(int i = 0; i < LL::g.size(); i++) {
      if(i == LL::uf.find(i)) cc[i] = ptr++;
    }

    t.resize(ptr);
    for(int i = 0; i < LL::g.size(); i++) {
      comp[i] = cc[LL::uf.find(i)];
    }

    vector< pair< int, int > > edges;
    for(int i = 0; i < LL::g.size(); i++) {
      for(auto &to : LL::g[i]) edges.emplace_back(minmax(i, to));
    }
    sort(begin(edges), end(edges));
    edges.erase(unique(begin(edges), end(edges)), end(edges));
    vector< pair< int, int > > vs;
    for(auto &e : edges) {
      int x = comp[e.first], y = comp[e.second];
      if(x == y) continue;
      vs.emplace_back(e.first, e.second);
      t[x].push_back(y);
      t[y].push_back(x);
    }
    sort(begin(vs), end(vs));
    return (vs);
  }
};
