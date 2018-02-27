templete< typename T = int >
void warshall_floyd(Matrix< T > &g)
{
  for(int k = 0; k < g.size(); k++) {
    for(int i = 0; i < g.size(); i++) {
      for(int j = 0; j < g.size(); j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}
