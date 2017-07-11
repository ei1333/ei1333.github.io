struct Lexicographically_Matching : Bipartite_Matching
{
  Lexicographically_Matching(int n) : Bipartite_Matching(n) {}

  int back(int k)   // 押し戻す
  {
    match[match[k]] = -1;
    match[k] = -1;
    ++timestamp;
    dfs(k);
    return (match[k]);
  }

  void decide(int k) // 決める
  {
    alive[match[k]] = 0;
    alive[k] = 0;
  }
};
