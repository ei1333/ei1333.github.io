vector< vector< int64_t > > get_combination(int N)
{
  vector< vector< int64_t > > mat(N + 1, vector< int64_t >(N + 1));
  for(int i = 0; i <= N; i++) {
    for(int j = 0; j <= i; j++) {
      mat[i][j] = (j == 0 || j == i ? 1 : mat[i - 1][j - 1] + mat[i - 1][j]);
    }
  }
  return (mat);
}

