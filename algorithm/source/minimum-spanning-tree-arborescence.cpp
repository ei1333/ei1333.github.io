template< typename T >
struct MinimumSpanningTree_Arborescence
{

  struct edge
  {
    int to;
    T cost;
  };
  vector< vector< edge > > graph;
  T INF;

  MinimumSpanningTree_Arborescence(size_t v) : INF(numeric_limits< T >::max()), graph(v) {}

  void add_edge(int a, int b, T x)
  {
    graph[a].emplace_back((edge) {b, x});
  }

  T build(vector< vector< edge > > &g, int start, T sum)
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
    vector< vector< edge > > fixgraph(renew.size());
    for(int i = 0; i < N; i++) {
      for(auto &e : g[i]) {
        if(scc[i] == scc[e.to]) continue;
        fixgraph[scc[i]].emplace_back((edge) {scc[e.to], e.cost - weight[e.to]});
      }
    }
    return (build(fixgraph, scc[start], sum));
  }

  T build(int start)
  {
    auto get = build(graph, start, 0);
    if(get >= INF) return (-1);
    return (get);
  }
};
