struct edge
{ 
  int to, cost;
};
typedef vector< vector< edge > > Graph;

pair< int, int > dfs(const Graph& graph, int idx, int prev)
{
  pair< int, int > ret = make_pair(0, -1);
  for(int i = 0; i < graph[idx].size(); i++) {
    if(graph[idx][i].to != prev){
      pair< int, int > cost = dfs(graph, graph[idx][i].to, idx);
      cost.first += graph[idx][i].cost;
      ret = max(ret, cost);
    }
  }
  return(ret);
}
int Diameter(Graph& tree)
{
  pair< int, int > p = dfs(tree, 0, -1);
  pair< int, int > q = dfs(tree, p.second, -1);
  return(q.first);
}
