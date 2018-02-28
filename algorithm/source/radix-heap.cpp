template< typename T >
struct RadixHeap
{
  using uint = unsigned;
  vector< pair< uint, T > > v[33];
  uint size, last;

  RadixHeap() : size(0), last(0) {}

  bool empty() const { return size == 0; }

  inline int getbit(int a)
  {
    return a ? 32 - __builtin_clz(a) : 0;
  }

  void push(uint key, const T &value)
  {
    ++size;
    v[getbit(key ^ last)].emplace_back(key, value);
  }

  pair< uint, T > pop()
  {
    if(v[0].empty()) {
      int idx = 1;
      while(v[idx].empty()) ++idx;
      last = min_element(begin(v[idx]), end(v[idx]))->first;
      for(auto &p : v[idx]) v[getbit(p.first ^ last)].emplace_back(p);
      v[idx].clear();
    }
    --size;
    auto ret = v[0].back();
    v[0].pop_back();
    return ret;
  }
};
