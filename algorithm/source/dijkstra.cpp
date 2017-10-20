struct edge
{
  int to, cost;
};
typedef vector< vector < edge > > Graph;

template< typename T = int >
vector< T > Dijkstra(Graph &g, int s)
{
  typedef pair< T, int > Pi;

  vector< T > min_cost(g.size(), numeric_limits< T >::max());
  priority_queue< Pi, vector< Pi >, greater< Pi > > que;
  que.emplace(0, s);
  min_cost[s] = 0;
  while(!que.empty()) {
    auto p = que.top();
    que.pop();
    if(p.first > min_cost[p.second]) continue;
    for(auto &e : g[p.second]) {
      if(p.first + e.cost >= min_cost[e.to]) continue;
      min_cost[e.to] = p.first + e.cost;
      que.emplace(min_cost[e.to], e.to);
    }
  }
  return (min_cost);
}
