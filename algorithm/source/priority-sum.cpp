template< typename T >
struct PrioritySumStructure
{
  static const bool INCREASE = false;
  static const bool DECREASE = true;
 
  bool order;
  int k, sz;
  T sum;
  set< pair< T, int > > add, pend;
  map< int, T > adding, pending;
 
  PrioritySumStructure(int k, bool order = INCREASE) : k(k), sum(0), sz(0), order(order) {}
 
  void Sweep()
  {
    while(sz < k && !pend.empty()) {
      auto p = order ? --pend.end() : pend.begin();
      sum += p->first;
      ++sz;
      add.emplace(*p);
      adding.emplace(p->second, p->first);
      pending.erase(p->second);
      pend.erase(p);
    }
    while(sz > k) {
      auto p = order ? add.begin() : --add.end();
      sum -= p->first;
      --sz;
      pend.emplace(*p);
      pending.emplace(p->second, p->first);
      adding.erase(p->second);
      add.erase(p);
    }
  }
 
  T getSum()
  {
    if(sz < k) throw ("get Sum Exception");
    return (sum);
  }
 
  void addElement(int k, T x)
  {
    if(adding.count(k) || pending.count(k)) {
      throw ("Add Element Exception");
    }
    ++sz;
    add.emplace(x, k);
    adding[k] = x;
    sum += x;
    Sweep();
  }
 
  void deleteElement(int k)
  {
    if(pending.count(k)) {
      pend.erase({pending[k], k});
      pending.erase(k);
    } else if(adding.count(k)) {
      --sz;
      sum -= adding[k];
      add.erase({adding[k], k});
      adding.erase(k);
      Sweep();
    } else {
      throw ("delete Element Exception");
    }
  }
 
  void incrementSize()
  {
    ++k;
    Sweep();
  }
 
  void decrementSize()
  {
    if(k == 0) throw ("decrement Size Exception");
    --k;
    Sweep();
  }
};
