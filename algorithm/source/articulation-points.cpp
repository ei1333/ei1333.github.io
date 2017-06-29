struct ArticulationPoints : LowLink
{
  ArticulationPoints(size_t v) : LowLink(v) {}

  vector< int > build()
  {
    LowLink::dfs();
    vector< int > vs;
    int sum = 0;
    for(int i = g.size() - 1; i >= 1; i--) {
      if(parent[i] == 0) ++sum;
      else if(ord[parent[i]] <= low[i]) vs.push_back(parent[i]);
    }
    if(sum > 1)vs.push_back(0);
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));
    return (vs);
  }
};
