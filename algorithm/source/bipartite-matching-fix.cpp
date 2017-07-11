struct Fix_Matching : Bipartite_Matching
{
  Fix_Matching(int sz) : Bipartite_Matching(sz) {}

  int add(int k) // 加える
  {
    alive[k] = 1;
    ++timestamp;
    return (dfs(k));
  }

  int kill(int k) // 消す
  {
    alive[k] = 0;
    if(match[k] == -1) return (0);
    match[match[k]] = -1;
    ++timestamp;
    int ret = dfs(match[k]);
    match[k] = -1;
    return (ret - 1);
  }
};
