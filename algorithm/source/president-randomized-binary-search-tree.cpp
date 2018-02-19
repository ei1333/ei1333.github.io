template< class Monoid, class OperatorMonoid = Monoid >
struct PresidentRandomizedBinarySearchTree : RandomizedBinarySearchTree< Monoid, OperatorMonoid >
{
  using RBST = RandomizedBinarySearchTree< Monoid, OperatorMonoid >;
  using Node = typename RBST::Node;
  using F = typename RBST::F;
  using G = typename RBST::G;
  using H = typename RBST::H;
  using P = typename RBST::P;

  PresidentRandomizedBinarySearchTree(int sz, const F &f, const Monoid &M1) :
      RBST(sz, f, M1) {}

  PresidentRandomizedBinarySearchTree(int sz, const F &f, const G &g, const H &h, const P &p,
                                      const Monoid &M1, const OperatorMonoid &OM0) :
      RBST(sz, f, g, h, p, M1, OM0) {}

  Node *clone(Node *t) override { return &(RBST::pool[RBST::ptr++] = *t); }

  Node *rebuild(Node *r) { return RBST::build(RBST::dump(r)); }
};
