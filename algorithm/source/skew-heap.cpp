template< typename T >
struct SkewHeap
{
  struct Node
  {
    T key, lazy;
    Node *l, *r;
  } *root = nullptr;
  bool rev;

  SkewHeap(bool rev = false) : rev(rev) {}

  Node *propagate(Node *t)
  {
    if(t->lazy != 0) {
      if(t->l) t->l->lazy += t->lazy;
      if(t->r) t->r->lazy += t->lazy;
      t->key += t->lazy;
      t->lazy = 0;
    }
    return t;
  }

  Node *merge(Node *x, Node *y)
  {
    if(!x || !y) return x ? x : y;
    propagate(x), propagate(y);
    if((x->key > y->key) ^ rev) swap(x, y);
    x->r = merge(y, x->r);
    swap(x->l, x->r);
    return x;
  }

  Node *push(const T &key)
  {
    auto t = new Node({key, 0, nullptr, nullptr});
    root = merge(root, t);
  }

  T top()
  {
    return propagate(root)->key;
  }

  void pop()
  {
    propagate(root);
    auto *temp = root;
    root = merge(root->l, root->r);
    delete temp;
  }

  bool empty() const
  {
    return !root;
  }

  void add(const T &lazy)
  {
    if(root) {
      root->lazy += lazy;
      propagate(root);
    }
  }

  void merge(SkewHeap< T > &p)
  {
    root = merge(root, p.root);
  }
};
