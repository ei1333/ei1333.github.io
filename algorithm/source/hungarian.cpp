template< typename T = int >
T Hungarian(vector< vector< T > > &A)
{
  const T infty = numeric_limits< T >::max();
  const int N = (int) A.size() - 1;
  const int M = (int) A[0].size() - 1;
  vector< int > P(M + 1), way(M + 1);
  vector< T > U(N + 1, 0), V(M + 1, 0), minV;
  vector< bool > used;

  for(int i = 1; i <= N; i++) {
    P[0] = i;
    minV.assign(M + 1, infty);
    used.assign(M + 1, false);
    int j0 = 0;
    while(P[j0] != 0) {
      int i0 = P[j0], j1 = 0;
      used[j0] = true;
      T delta = infty;
      for(int j = 1; j <= M; j++) {
        if(used[j]) continue;
        T curr = A[i0][j] - U[i0] - V[j];
        if(curr < minV[j]) minV[j] = curr, way[j] = j0;
        if(minV[j] < delta) delta = minV[j], j1 = j;
      }
      for(int j = 0; j <= M; j++) {
        if(used[j]) U[P[j]] += delta, V[j] -= delta;
        else minV[j] -= delta;
      }
      j0 = j1;
    }
    do {
      P[j0] = P[way[j0]];
      j0 = way[j0];
    } while(j0 != 0);
  }
  return (-V[0]);
}
