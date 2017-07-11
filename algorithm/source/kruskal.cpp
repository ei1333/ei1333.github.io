struct edge
{
  int u, v, cost;
  bool operator<(const edge& e) const
  {
    return(cost < e.cost);
  };
};
template< class T = int >
T kruskal(vector< edge > &edges, int V)
{
  sort(edges.begin(), edges.end());
  UnionFind tree(V);
  T ret = 0;
  for(auto& e : edges) {
    if(tree.unite(e.u, e.v)) ret += e.cost;
  }
  return (ret);
}
