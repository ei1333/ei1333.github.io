template< typename T >
struct PairingHeap
{
  struct Node
  {
    T key;
    Node *head, *next;
  } *root = nullptr;
  bool rev;

  PairingHeap(bool rev = false) : rev(rev) {}

  Node *merge(Node *x, Node *y)
  {
    if(!x || !y) return x ? x : y;
    if((x->key > y->key) ^ rev) swap(x, y);
    y->next = x->head;
    x->head = y;
    return x;
  }

  Node *push(const T &key)
  {
    auto t = new Node({key, nullptr, nullptr});
    root = merge(root, t);
  }

  T top()
  {
    return root->key;
  }

  Node *_pop(Node *s)
  {
    Node *p = nullptr;
    while(s) {
      Node *a = s, *b = nullptr;
      s = s->next;
      a->next = nullptr;
      if(s) {
        b = s;
        s = s->next;
        b->next = nullptr;
      }
      a = merge(a, b);
      a->next = p;
      p = a;
    }
    while(p) {
      Node *j = p;
      p = p->next;
      s = merge(j, s);
    }
    return s;
  }

  void pop()
  {
    auto *temp = root;
    root = _pop(root->head);
  }

  bool empty() const
  {
    return !root;
  }

  void merge(PairingHeap< T > &p)
  {
    root = merge(root, p.root);
  }
};
