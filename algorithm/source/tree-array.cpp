struct TreeArray : CentroidPathDecomposition
{
  TreeArray(int sz) : CentroidPathDecomposition(sz) {}

  vector< int > index;

  void Build()
  {
    CentroidPathDecomposition::Build();
    int ptr = 0;
    for(auto &centroid : Centroids) {
      index.emplace_back(ptr);
      ptr += centroid.size();
    }
  }

  inline int get(int a)
  {
    return (index[a]);
  }

  inline void query(int a, int b, const function< void(int, int) > &f)
  {
    int TreeIdxA, TreeDepthA, TreeIdxB, TreeDepthB;
    tie(TreeIdxA, TreeDepthA) = Information(a);
    tie(TreeIdxB, TreeDepthB) = Information(b);
    while(TreeIdxA != TreeIdxB) {
      if(Centroids[TreeIdxA].Deep > Centroids[TreeIdxB].Deep) {
        f(index[TreeIdxA], index[TreeIdxA] + TreeDepthA + 1);
        tie(TreeIdxA, TreeDepthA) = Centroids[TreeIdxA].Up();
      } else {
        f(index[TreeIdxB], index[TreeIdxB] + TreeDepthB + 1);
        tie(TreeIdxB, TreeDepthB) = Centroids[TreeIdxB].Up();
      }
    }
    if(TreeDepthA > TreeDepthB) swap(TreeDepthA, TreeDepthB);
    f(index[TreeIdxA] + TreeDepthA, index[TreeIdxA] + TreeDepthB + 1);
  }
};
