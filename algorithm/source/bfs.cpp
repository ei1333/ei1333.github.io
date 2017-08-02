int W, H;
char mas[500][500];
int min_cost[500][500];
 
int bfs(int sx, int sy, char c)
{
  const int vx[] = {0, 1, 0, -1}, vy[] = {1, 0, -1, 0};
  memset(min_cost, -1, sizeof(min_cost));
   
  queue< pair< int, int > > que;
  que.emplace(sx, sy);
  min_cost[sx][sy] = 0;
 
  while(!que.empty()) {
    auto p = que.front(); que.pop();
    if(mas[p.second][p.first] == c) return(min_cost[p.first][p.second]);
    for(int i = 0; i < 4; i++) {
      int nx = p.first + vx[i], ny = p.second + vy[i];
      if(nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
      if(min_cost[nx][ny] != -1) continue;
      if(mas[ny][nx] == '#') continue;
      min_cost[nx][ny] = min_cost[p.first][p.second] + 1;
      que.emplace(nx, ny);
    }
  }
  return(-1);
}
