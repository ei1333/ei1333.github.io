template< typename T = int >
void AddEdge(vector< vector< T > > &g, int s, int t, T cost)
{
  g[s][t] = g[t][s] = min(g[s][t], cost);
  for(int k : {s, t}) {
    for(int i = 0; i < g.size(); i++) {
      for(int j = 0; j < g.size(); j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}
