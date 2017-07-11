template< class T >
struct DecomposableSearchingStructure
{
  struct DecomposableSearchingProblem
  {
    T structure;
    int length;

    DecomposableSearchingProblem(T t, int l) : structure(t), length(l) {}

    DecomposableSearchingProblem operator+(const DecomposableSearchingProblem &p)
    {
      return (DecomposableSearchingProblem(structure + p.structure, length + p.length));
    }
  };

  vector< DecomposableSearchingProblem > vs;

  DecomposableSearchingStructure() {}

  void add(const T &st)
  {
    vs.emplace_back(DecomposableSearchingProblem(st, 1));
    while(vs.size() > 1 && vs[vs.size() - 2].length == vs[vs.size() - 1].length) {
      DecomposableSearchingProblem renew(vs[vs.size() - 2] + vs[vs.size() - 1]);
      vs.pop_back(), vs.pop_back();
      vs.push_back(renew);
    }
  }

  size_t size()
  {
    return (vs.size());
  }

  T &operator[](int k)
  {
    return (vs[k].structure);
  }
};
