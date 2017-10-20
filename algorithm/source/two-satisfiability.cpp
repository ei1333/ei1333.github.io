struct TwoSatisfiability : StronglyConnectedComponents
{
  int sz;

  TwoSatisfiability(size_t v) : sz(v), StronglyConnectedComponents(v + v) {}

  void add_literal(int u, int v)
  {
    add_edge(rev(u), v);
    add_edge(rev(v), u);
  }

  void add_literal(int u)
  {
    add_edge(u, u);
  }

  inline int rev(int x)
  {
    if(x >= sz) return (x - sz);
    return (x + sz);
  }

  bool operator()(int v)
  {
    return ((*this)[v] > (*this)[rev(v)]);
  }

  bool solve()
  {
    vector< vector< int > > g;
    build(g);
    for(int i = 0; i < sz; i++) {
      if((*this)[i] == (*this)[rev(i)]) return (false);
    }
    return (true);
  }
};

