void rec(int idx, int left, int right, int latte, int malta)
{
  if(left >= right) return;
  int mid = (left + right) >> 1;
  dp[idx][mid] = INF;
  int best = -1;
  for(int k = latte; k < min(mid, malta); k++) {
    int64 cost = dp[idx - 1][k] + getcost(k, mid); // cost[k, mid)
    if(cost < dp[idx][mid]) {
      dp[idx][mid] = cost;
      best = k;
    }
  }
  rec(idx, left, mid, latte, best + 1);
  rec(idx, mid + 1, right, best, malta);
}

/* initialize dp[0][0] = 0 */
/* call rec([1,m], 0, N + 1, 0, N + 1) */


