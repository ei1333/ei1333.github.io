const int MAX_N = 100000;

vector< int > g[MAX_N];
int sub[MAX_N];
bool v[MAX_N];

int build_dfs(int idx, int par)
{
  sub[idx] = 1;
  for(auto &to : g[idx]) {
    if(to == par || v[to]) continue;
    sub[idx] += build_dfs(to, idx);
  }
  return (sub[idx]);
}

pair< int, int > search_centroid(int idx, int par, const int all)
{
  pair< int, int > ret(INF, -1);
  int connect = all - sub[idx];
  for(auto &to : g[idx]) {
    if(to == par || v[to]) continue;
    ret = min(ret, search_centroid(to, idx, all));
    connect = max(connect, sub[to]);
  }
  return (min(ret, make_pair(connect, idx)));
}

void beet(int idx)
{

}

void centroid_decomp(int idx)
{
  int centroid = search_centroid(idx, -1, build_dfs(idx, -1)).second;
  beet(centroid);
  v[centroid] = true;
  for(auto &to : g[centroid]) {
    if(v[to]) continue;
    centroid_decomp(to);
  }
}
