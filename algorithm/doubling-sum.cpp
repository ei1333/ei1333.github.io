struct DoublingSum
{
  const int LOG;
  vector< vector< int > > table, sum;

  DoublingSum(int sz) : LOG(32 - __builtin_clz(sz))
  {
    table.assign(LOG, vector< int >(sz, -1));
    sum.assign(LOG, vector< int >(sz, 0));
  }

  int set_next(int k, int x, int v)
  {
    table[0][k] = x;
    sum[0][k] = v;
  }

  void build()
  {
    for(int k = 0; k + 1 < LOG; k++) {
      for(int i = 0; i < table.size(); i++) {
        if(table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
    for(int k = 0; k + 1 < LOG; k++) {
      for(int i = 0; i < table.size(); i++) {
        if(table[k][i] == -1) continue;
        else sum[k + 1][i] = sum[k][i] + sum[k][table[k][i]];
      }
    }
  }

  int query(int k, int t)
  {
    int ret = 0;
    for(int i = LOG - 1; i >= 0; i--) {
      if(k == -1) break;
      if((t >> i) & 1) {
        ret += sum[i][k];
        k = table[i][k];
      }
    }
    return (ret);
  }
};
