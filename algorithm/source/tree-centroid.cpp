const int MAX_N = 100000;

vector< int > g[MAX_N];
int sub[MAX_N], centroid_sz;
vector< int > centroid;

int build_dfs(int idx, int par)
{
  sub[idx] = 1;
  for(auto &to : g[idx]) {
    if(to == par) continue;
    if(v[to]) continue;
    sub[idx] += build_dfs(to, idx);
  }
  return (sub[idx]);
}
 
 
void build_centroid(int idx, int par, const int all)
{
  int connect = all - sub[idx];
  for(auto &to : g[idx]) {
    if(to == par) continue;
    if(v[to]) continue;
    build_centroid(to, idx, all);
    connect = max(connect, sub[to]);
  }
  if(connect < centroid_sz) {
    centroid_sz = connect;
    centroid.clear();
  }
  if(connect == centroid_sz) {
    centroid.emplace_back(idx);
  }
}

vector< int > get_centroid(int root)
{
  centroid.clear();
  centroid_sz = INF;
  build_centroid(root, -1, build_dfs(root, -1));
  return(centroid);
}
