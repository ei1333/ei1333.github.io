struct Bipartite_Matching
{
  vector< vector< int > > graph;
  vector< int > match, alive, used;
  int timestamp;
 
  Bipartite_Matching(int n)
  {
    timestamp = 0;
    graph.resize(n);
    alive.assign(n, 1);
    used.assign(n, 0);
    match.assign(n, -1);
  }
 
  void add_edge(int u, int v)
  {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
 
  bool dfs(int v)
  {
    used[v] = timestamp;
    for(int i = 0; i < graph[v].size(); i++) {
      int u = graph[v][i], w = match[u];
      if(alive[u] == 0) continue;
      if(w == -1 || (used[w] != timestamp && dfs(w))) {
        match[v] = u;
        match[u] = v;
        return (true);
      }
    }
    return (false);
  }
 
  int bipartite_matching()
  {
    int ret = 0;
    for(int i = 0; i < graph.size(); i++) {
      if(alive[i] == 0) continue;
      if(match[i] == -1) {
        ++timestamp;
        ret += dfs(i);
      }
    }
    return (ret);
  } 
};
