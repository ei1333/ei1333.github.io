template< typename T >
struct MinimumSpanningTreeArborescence
{
  WeightedGraph< T > g;
  T INF;

  MinimumSpanningTreeArborescence(const WeightedGraph< T > g) : INF(numeric_limits< T >::max()), g(g) {}

  T build(WeightedGraph< T > &g, int start, T sum)
  {
    int N = (int) g.size();

    vector< int > rev(N, -1);
    vector< T > weight(N, INF);
    for(int idx = 0; idx < N; idx++) {
      for(auto &e : g[idx]) {
        if(e.cost < weight[e.to]) {
          weight[e.to] = e.cost;
          rev[e.to] = idx;
        }
      }
    }

    StronglyConnectedComponents scc(N);
    for(int idx = 0; idx < N; idx++) {
      if(start == idx) continue;
      if(rev[idx] == -1) return (INF);
      scc.add_edge(rev[idx], idx);
      sum += weight[idx];
    }
    vector< vector< int > > renew;
    scc.build(renew);
    if(renew.size() == N) return (sum);
    WeightedGraph< T > fixgraph(renew.size());
    for(int i = 0; i < N; i++) {
      for(auto &e : g[i]) {
        if(scc[i] == scc[e.to]) continue;
        fixgraph[scc[i]].emplace_back(scc[e.to], e.cost - weight[e.to]);
      }
    }
    return (build(fixgraph, scc[start], sum));
  }

  T build(int start)
  {
    auto get = build(g, start, 0);
    if(get >= INF) return (-1);
    return (get);
  }
};
