using KEY = int;
using VALUE = int;

namespace Beet
{
  inline int xor128()
  {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123;
    int t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  struct MyNode
  {
    const KEY key;
    VALUE value;
    MyNode *Lch, *Rch;
    int subtree;

    MyNode(KEY key, VALUE value) : key(key), value(value), subtree(1), Lch(nullptr), Rch(nullptr) {}
  };

  inline int count(MyNode *t)
  {
    if(t == nullptr) return (0);
    else return (t->subtree);
  }
  
  inline void push(MyNode *t)
  {
    //
  }

  inline MyNode *update(MyNode *t)
  {
    if(t == nullptr) return (nullptr);
    t->subtree = count(t->Lch) + count(t->Rch) + 1;
    return (t);
  }

  inline MyNode *makenode(int key, int value)
  {
    return (new MyNode(key, value));
  }

  inline MyNode *node_merge(MyNode *l, MyNode *r)
  {
    push(l);
    push(r);
    if(l == nullptr) return (r);
    if(r == nullptr) return (l);
    if(xor128() % (count(l) + count(r)) < count(l)) {
      l->Rch = node_merge(l->Rch, r);
      return (update(l));
    } else {
      r->Lch = node_merge(l, r->Lch);
      return (update(r));
    }
  }

  pair< MyNode *, MyNode * > node_split(MyNode *t, int k) // [0, k), [k, n)
  {
    push(t);
    if(t == nullptr) return {nullptr, nullptr};
    if(k <= count(t->Lch)) {
      auto s = node_split(t->Lch, k);
      t->Lch = s.second;
      return (make_pair(s.first, update(t)));
    } else {
      auto s = node_split(t->Rch, k - count(t->Lch) - 1);
      t->Rch = s.first;
      return (make_pair(update(t), s.second));
    }
  }

  struct RBSTMap
  {
  private:
    MyNode *root;
  public:
    RBSTMap() : root(nullptr) {};

    RBSTMap(MyNode *root) : root(root) {}

    inline MyNode *insert(const KEY &key, const VALUE &value)
    {
      auto p = lower_bound_both(key);
      assert(p.second == nullptr || p.second->key != key);
      auto q = makenode(key, value);
      auto r = node_split(root, p.first);
      root = node_merge(node_merge(r.first, q), r.second);
      return (q);
    }

    inline void erase(const KEY &key)
    {
      auto p = lower_bound_both(key);
      assert(p.second != nullptr && p.second->key == key);
      auto q = node_split(root, p.first);
      auto r = node_split(q.second, 1);
      delete r.first;
      root = node_merge(q.first, r.second);
    }

    inline int size()
    {
      return (count(root));
    }

    inline bool empty()
    {
      return (root == nullptr);
    }

    inline MyNode *find(const KEY &key)
    {
      auto p = lower_bound_both(key);
      if(p.second == nullptr) return (nullptr);
      if(p.second->key == key) return (p.second);
      return (nullptr);
    }

    inline MyNode *operator[](const KEY &key)
    {
      auto p = lower_bound_both(key);
      if(p.second == nullptr) return (insert(key, -1));
      if(p.second->key != key) return (insert(key, -1));
      return (p.second);
    }

  private:
    inline pair< int, MyNode * > lower_bound_both(MyNode *t, const KEY &key)
    {
      if(root == nullptr) return {0, nullptr};
      if(key == t->key) return {0, t};
      if(key < t->key) return (lower_bound_both(t->Lch, key));
      auto p = lower_bound_both(t->Rch, key);
      p.first += count(t->Lch) + 1;
      return (p);
    }

    inline pair< int, MyNode * > lower_bound_both(const KEY &key)
    {
      return (lower_bound_both(root, key));
    }

  public:
    inline MyNode *lower_bound(const KEY &key)
    {
      return (lower_bound_both(root, key).second);
    }

    inline pair< RBSTMap, RBSTMap > split(int k)
    {
      auto p = node_split(root, k);
      return {RBSTMap(p.first), RBSTMap(p.second)};
    }

    inline static RBSTMap merge(RBSTMap a, RBSTMap b)
    {
      return (RBSTMap(node_merge(a.root, b.root)));
    }
  };
};
