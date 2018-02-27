template< typename G >
struct TreeArray : CentroidPathDecomposition< G >
{
  using CPD = CentroidPathDecomposition< G >;

  TreeArray(const G &g) : CPD(g) {}

  vector< int > index;

  void Build()
  {
    CPD::Build();
    int ptr = 0;
    for(auto &centroid : CPD::Centroids) {
      index.emplace_back(ptr);
      ptr += centroid.size();
    }
  }

  inline int get(int a)
  {
    auto p = CPD::Information(a);
    return (index[p.first] + p.second);
  }

  inline void query(int a, int b, const function< void(int, int) > &f)
  {
    int TreeIdxA, TreeDepthA, TreeIdxB, TreeDepthB;
    tie(TreeIdxA, TreeDepthA) = CPD::Information(a);
    tie(TreeIdxB, TreeDepthB) = CPD::Information(b);
    while(TreeIdxA != TreeIdxB) {
      if(CPD::Centroids[TreeIdxA].Deep > CPD::Centroids[TreeIdxB].Deep) {
        f(index[TreeIdxA], index[TreeIdxA] + TreeDepthA + 1);
        tie(TreeIdxA, TreeDepthA) = CPD::Centroids[TreeIdxA].Up();
      } else {
        f(index[TreeIdxB], index[TreeIdxB] + TreeDepthB + 1);
        tie(TreeIdxB, TreeDepthB) = CPD::Centroids[TreeIdxB].Up();
      }
    }
    if(TreeDepthA > TreeDepthB) swap(TreeDepthA, TreeDepthB);
    f(index[TreeIdxA] + TreeDepthA, index[TreeIdxA] + TreeDepthB + 1);
  }
};
