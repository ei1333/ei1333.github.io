int64 rec(int left, int right)
{
  if(~dp[left][right]) return (dp[left][right]);
  if(left + 1 >= right) {
    opt[left][right] = left;
    return (0);
  }
  rec(left, right - 1);
  rec(left + 1, right);
  dp[left][right] = INF;
  for(int k = opt[left][right - 1]; k <= opt[left + 1][right]; k++) {
    int64 cost = rec(left, k) + rec(k, right);
    if(cost < dp[left][right]) {
      dp[left][right] = cost;
      opt[left][right] = k;
    }
  }
  return (dp[left][right] += getcost(left, right));
}

/* initialize memset(dp, -1, sizeof(dp)) */
/* call rec(0, N) */
