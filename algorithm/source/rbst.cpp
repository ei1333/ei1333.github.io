int xor128(void) { 
  static int x = 123456789;
  static int y = 362436069;
  static int z = 521288629;
  static int w = 88675123; 
  int t;
   
  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
  
struct Node {
  int Value;
  int SubTreeSize;
  Node *Lch, *Rch;
  int RMQ;
  
  Node(int V):Value(V), SubTreeSize(1), RMQ(V) {
    Lch = (Node *)NULL;
    Rch = (Node *)NULL;
  };
};
inline int Count(Node *t)
{
  if(t == (Node *)NULL) return(0);
  else return(t -> SubTreeSize);
}
inline int Sum(Node *t)
{
  if(t == (Node *)NULL) return(INF);
  else return(t -> RMQ);
}
  
inline Node *Update(Node *t)
{
  t -> SubTreeSize = Count(t -> Lch) + Count(t -> Rch) + 1;
  t -> RMQ = min(Sum(t -> Lch), min(Sum(t -> Rch), t -> Value));
  return(t);
}
  
inline Node *MakeRoot(int value)
{
  return(new Node(value));
}
  
Node *Merge(Node *l, Node *r)
{
  if(l == (Node *)NULL) return(r);
  if(r == (Node *)NULL) return(l);
  int Left  = l -> SubTreeSize;
  int Right = r -> SubTreeSize;
  if(xor128() % (Left + Right) < Left) {
    l -> Rch = Merge(l -> Rch, r);
    return(Update(l));
  } else {
    r -> Lch = Merge(l, r -> Lch);
    return(Update(r));
  }
}
    
pair< Node*, Node* > Split(Node *t, int k) // [0, k), [k, n)
{
  if(t == (Node *)NULL) return(make_pair((Node *)NULL, (Node *)NULL));
  if(k <= Count(t -> Lch)) {
    pair< Node *, Node *> s = Split(t -> Lch, k);
    t -> Lch = s.second;
    return(make_pair(s.first, Update(t)));
  } else {
    pair< Node *, Node *> s = Split(t -> Rch, k - Count(t -> Lch) - 1);
    t -> Rch = s.first;
    return(make_pair(Update(t), s.second));
  }
}
  
Node *Insert(Node *root, int pos, int value)
{
  Node *p = MakeRoot(value);
  pair< Node *, Node *> s = Split(root, pos);
  return(Merge(Merge(s.first, p), s.second));
}
 
Node *Erase(Node *root, int pos)
{
  pair< Node *, Node *> s = Split(root, pos);
  pair< Node *, Node *> t = Split(s.second, 1);
  delete t.first;
  return(Merge(s.first, t.second));
}
 
int Lower_Bound(Node *root, int Value)
{
  if(root == (Node *)NULL) return(0);
  if(Value < root -> Value) return(Lower_Bound(root -> Lch, Value));
  return(Lower_Bound(root -> Rch, Value) + Count(root -> Lch) + 1);
}
  
Node *Insert(Node *root, int Value)
{
  return(Insert(root, Lower_Bound(root, Value), Value));
} 
 
void Dump(Node *root)
{
  if(root == (Node *)NULL) return;
  cout << "(";
  Dump(root -> Lch);
  cout << "" << root -> Value << "";
  Dump(root -> Rch);
  cout << ")";
}
