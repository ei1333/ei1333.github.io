struct Doubling
{
  const int LOG;
  vector< vector< int > > table;

  Doubling(int sz) : LOG(32 - __builtin_clz(sz))
  {
    table.assign(LOG, vector< int >(sz, -1));
  }

  int set_next(int k, int x)
  {
    table[0][k] = x;
  }

  void build()
  {
    for(int k = 0; k + 1 < LOG; k++) {
      for(int i = 0; i < table.size(); i++) {
        if(table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
  }

  int query(int k, int t)
  {
    for(int i = LOG - 1; i >= 0; i--) {
      if(k == -1) break;
      if((t >> i) & 1) k = table[i][k];
    }
    return (k);
  }
};
