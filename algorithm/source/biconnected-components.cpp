struct BiConnectedComponents : LowLink
{
  vector< pair< int, int > > edges;
  vector< int > comp;

  BiConnectedComponents(size_t v) : LowLink(v), comp(v) {}

  void add_edge(int x, int y)
  {
    LowLink::add_edge(x, y);
    edges.push_back(minmax(x, y));
  }

  int operator[](int k)
  {
    return (comp[k]);
  }

  vector< pair< int, int > > build(vector< vector< int > > &t)
  {
    LowLink::dfs();
    int ptr = 0;
    vector< int > cc(g.size());
    for(int i = 0; i < g.size(); i++) {
      if(i == uf.find(i)) cc[i] = ptr++;
    }

    t.resize(ptr);
    for(int i = 0; i < g.size(); i++) {
      comp[i] = cc[uf.find(i)];
    }
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
