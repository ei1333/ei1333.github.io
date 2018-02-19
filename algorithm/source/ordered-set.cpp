template< class T >
struct OrderedSet : OrderedMultiSet< T >
{
  using SET = OrderedMultiSet< T >;
  using RBST = typename SET::RBST;
  using Node = typename RBST::Node;

  OrderedSet(int sz) : OrderedMultiSet< T >(sz) {}

  void insert_key(Node *&t, const T &x) override
  {
    if(SET::count(t, x)) return;
    RBST::insert(t, SET::lower_bound(t, x), x);
  }
};
