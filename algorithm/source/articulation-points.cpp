template< typename G >
struct ArticulationPoints : LowLink< G >
{
  using LL = LowLink< G >;

  ArticulationPoints(const G &g) : LL(g) {}

  vector< int > build()
  {
    LL::dfs();
    vector< int > vs;
    int sum = 0;
    for(int i = LL::g.size() - 1; i >= 1; i--) {
      if(LL::parent[i] == 0) ++sum;
      else if(LL::ord[LL::parent[i]] <= LL::low[i]) {
        vs.emplace_back(LL::parent[i]);
      }
    }
    if(sum > 1) vs.push_back(0);
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));
    return (vs);
  }
};

