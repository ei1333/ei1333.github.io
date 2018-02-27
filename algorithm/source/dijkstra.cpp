template< typename T >
struct WeightedGraph
{
  struct edge
  {
    int to;
    T cost;
  };
 
  vector< vector< edge > > g;
 
  WeightedGraph() {}
 
  WeightedGraph(int n) : g(n) {}
 
  void add_edge(int u, int v, T cost)
  {
    g[u].emplace_back((edge) {v, cost});
  }
 
  vector< edge > &operator[](int k)
  {
    return g[k];
  }
 
  size_t size() const
  {
    return g.size();
  }
};

template< typename T >
vector< T > dijkstra(WeightedGraph< T > &g, int s)
{
  const auto INF = numeric_limits< T >::max();
  vector< T > dist;
  dist.assign(g.size(), INF);
 
  using Pi = pair< T, int >;
  priority_queue< Pi, vector< Pi >, greater< Pi > > que;
  dist[s] = 0;
  que.emplace(dist[s], s);
  while(!que.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = que.top();
    que.pop();
    if(dist[idx] < cost) continue;
    for(auto &e : g[idx]) {
      auto next_cost = cost + e.cost;
      if(dist[e.to] <= next_cost) continue;
      dist[e.to] = next_cost;
      que.emplace(dist[e.to], e.to);
    }
  }
  return dist;
}
