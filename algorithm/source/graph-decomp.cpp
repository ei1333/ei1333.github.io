template< typename G >
G decomp_graph(const G &g, const vector< int > &vertex) {
  G f(vertex.size());
  for(int i = 0; i < vertex.size(); i++) {
    for(auto e : g[vertex[i]]) {
      e = lower_bound(begin(vertex), end(vertex), e) - begin(vertex);
      f[i].emplace_back(e);
    }
  }
  return f;
}
