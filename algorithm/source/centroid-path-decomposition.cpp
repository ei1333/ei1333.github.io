template< typename G >
struct CentroidPathDecomposition
{
  struct Centroid
  {
    int ParIndex, ParDepth, Deep;
    vector< int > node;

    Centroid(int idx, int dep, int deep) : ParIndex(idx), ParDepth(dep), Deep(deep) {}

    inline size_t size()
    {
      return (node.size());
    }

    inline int &operator[](int k)
    {
      return (node[k]);
    }

    inline pair< int, int > Up()
    {
      return (make_pair(ParIndex, ParDepth));
    }
  };

  const G &graph;
  vector< int > SubTreeSize, NextPath;
  vector< int > TreeIndex, TreeDepth;
  vector< Centroid > Centroids;

  void BuildSubTreeSize()
  {
    stack< pair< int, int > > s;
    s.emplace(0, -1);
    while(!s.empty()) {
      auto p = s.top();
      s.pop();
      if(~SubTreeSize[p.first]) {
        NextPath[p.first] = -1;
        for(auto &to : graph[p.first]) {
          if(p.second == to) continue;
          SubTreeSize[p.first] += SubTreeSize[to];
          if(NextPath[p.first] == -1 || SubTreeSize[NextPath[p.first]] < SubTreeSize[to]) {
            NextPath[p.first] = to;
          }
        }
      } else {
        s.push(p);
        SubTreeSize[p.first] = 1;
        for(auto &to : graph[p.first]) {
          if(p.second != to) s.emplace(to, p.first);
        }
      }
    }
  }

  void BuildPath()
  {
    stack< pair< int, int > > s;
    Centroids.emplace_back(-1, -1, 0);
    s.emplace(0, -1);
    TreeIndex[0] = 0;
    while(!s.empty()) {
      auto p = s.top();
      s.pop();
      TreeDepth[p.first] = (int) Centroids[TreeIndex[p.first]].size();
      for(auto &to : graph[p.first]) {
        if(p.second == to) continue;
        if(to == NextPath[p.first]) { // Centroid-Path
          TreeIndex[to] = TreeIndex[p.first];
        } else {                  // Not Centroid-Path
          TreeIndex[to] = (int) Centroids.size();
          Centroids.emplace_back(TreeIndex[p.first], TreeDepth[p.first], Centroids[TreeIndex[p.first]].Deep + 1);
        }
        s.emplace(to, p.first);
      }
      Centroids[TreeIndex[p.first]].node.emplace_back(p.first);
    }
  }


  virtual void Build()
  {
    BuildSubTreeSize();
    BuildPath();
  }

  inline size_t size()
  {
    return (Centroids.size());
  }

  inline pair< int, int > Information(int idx)
  {
    return (make_pair(TreeIndex[idx], TreeDepth[idx]));
  }

  inline Centroid &operator[](int k)
  {
    return (Centroids[k]);
  }

  inline int LCA(int a, int b)
  {
    int TreeIdxA, TreeDepthA, TreeIdxB, TreeDepthB;
    tie(TreeIdxA, TreeDepthA) = Information(a);
    tie(TreeIdxB, TreeDepthB) = Information(b);
    while(TreeIdxA != TreeIdxB) {
      if(Centroids[TreeIdxA].Deep > Centroids[TreeIdxB].Deep) {
        tie(TreeIdxA, TreeDepthA) = Centroids[TreeIdxA].Up();
      } else {
        tie(TreeIdxB, TreeDepthB) = Centroids[TreeIdxB].Up();
      }
    }
    if(TreeDepthA > TreeDepthB) swap(TreeDepthA, TreeDepthB);
    return (Centroids[TreeIdxA][TreeDepthA]);
  }

  inline virtual void query(int a, int b, const function< void(int, int, int) > &f)
  {
    int TreeIdxA, TreeDepthA, TreeIdxB, TreeDepthB;
    tie(TreeIdxA, TreeDepthA) = Information(a);
    tie(TreeIdxB, TreeDepthB) = Information(b);
    while(TreeIdxA != TreeIdxB) {
      if(Centroids[TreeIdxA].Deep > Centroids[TreeIdxB].Deep) {
        f(TreeIdxA, 0, TreeDepthA + 1);
        tie(TreeIdxA, TreeDepthA) = Centroids[TreeIdxA].Up();
      } else {
        f(TreeIdxB, 0, TreeDepthB + 1);
        tie(TreeIdxB, TreeDepthB) = Centroids[TreeIdxB].Up();
      }
    }
    if(TreeDepthA > TreeDepthB) swap(TreeDepthA, TreeDepthB);
    f(TreeIdxA, TreeDepthA, TreeDepthB + 1);
  }

  CentroidPathDecomposition(const G &g) : graph(g)
  {
    int SZ = g.size();
    SubTreeSize.assign(SZ, -1);
    NextPath.resize(SZ);
    TreeIndex.resize(SZ);
    TreeDepth.resize(SZ);
  }
};
