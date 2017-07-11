struct Dinic
{
  const int INF = 1 << 30;

  struct edge
  {
    int to, cap, rev;
  };

  vector< vector< edge > > graph;
  vector< int > min_cost, iter;

  Dinic(int n)
  {
    graph.resize(n);
  }

  void add_edge(int from, int to, int cap)
  {
    graph[from].push_back((edge) {to, cap, (int) graph[to].size()});
    graph[to].push_back((edge) {from, 0, (int) graph[from].size() - 1});
  }

  bool bfs(int s, int t)
  {
    min_cost.assign(graph.size(), -1);
    queue< int > que;
    min_cost[s] = 0;
    que.push(s);
    while(!que.empty()) {
      int p = que.front();
      que.pop();
      for(int i = 0; i < graph[p].size(); i++) {
        const edge &e = graph[p][i];
        if(e.cap > 0 && min_cost[e.to] == -1) {
          min_cost[e.to] = min_cost[p] + 1;
          que.push(e.to);
        }
      }
    }
    return (min_cost[t] != -1);
  }

  int dfs(int idx, const int t, int flow)
  {
    if(idx == t) return (flow);
    for(int &i = iter[idx]; i < graph[idx].size(); i++) {
      edge &e = graph[idx][i];
      if(e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
        int d = dfs(e.to, t, min(flow, e.cap));
        if(d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          return (d);
        }
      }
    }
    return (0);
  }

  int max_flow(int s, int t)
  {
    int flow = 0;
    while(bfs(s, t)) {
      iter.assign(graph.size(), 0);
      int f = 0;
      while((f = dfs(s, t, INF)) > 0) {
        flow += f;
      }
    }
    return (flow);
  }
};
